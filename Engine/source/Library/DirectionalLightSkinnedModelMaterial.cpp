/*
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "DirectionalLightSkinnedModelMaterial.h"
#include "GameException.h"
#include "Mesh.h"
#include "Bone.h"

namespace Library
{
	RTTI_DEFINITIONS( DirectionalLightSkinnedModelMaterial )

		DirectionalLightSkinnedModelMaterial::DirectionalLightSkinnedModelMaterial()
		: Material( "main11" ),
		MATERIAL_VARIABLE_INITIALIZATION( WorldViewProjection ), MATERIAL_VARIABLE_INITIALIZATION( World ),
		MATERIAL_VARIABLE_INITIALIZATION( AmbientColor ), MATERIAL_VARIABLE_INITIALIZATION( LightDirection ),
		MATERIAL_VARIABLE_INITIALIZATION( BoneTransforms ), MATERIAL_VARIABLE_INITIALIZATION(ColorTexture)
	{ }

	MATERIAL_VARIABLE_DEFINITION( DirectionalLightSkinnedModelMaterial, WorldViewProjection )
	MATERIAL_VARIABLE_DEFINITION( DirectionalLightSkinnedModelMaterial, World )
	MATERIAL_VARIABLE_DEFINITION( DirectionalLightSkinnedModelMaterial, AmbientColor )
	MATERIAL_VARIABLE_DEFINITION( DirectionalLightSkinnedModelMaterial, LightDirection )
	MATERIAL_VARIABLE_DEFINITION( DirectionalLightSkinnedModelMaterial, BoneTransforms )
	MATERIAL_VARIABLE_DEFINITION( DirectionalLightSkinnedModelMaterial, ColorTexture )

		void DirectionalLightSkinnedModelMaterial::Initialize( Effect& effect )
	{
		Material::Initialize( effect );

		MATERIAL_VARIABLE_RETRIEVE( WorldViewProjection )
		MATERIAL_VARIABLE_RETRIEVE( World )
		MATERIAL_VARIABLE_RETRIEVE( AmbientColor )
		MATERIAL_VARIABLE_RETRIEVE( LightDirection )
		MATERIAL_VARIABLE_RETRIEVE( BoneTransforms )
		MATERIAL_VARIABLE_RETRIEVE( ColorTexture )

			D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEINDICES", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "WEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		CreateInputLayout( "main11", "p1", inputElementDescriptions, ARRAYSIZE( inputElementDescriptions ) );
	}

	void DirectionalLightSkinnedModelMaterial::CreateVertexBuffer( ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer ) const
	{
		const std::vector<XMFLOAT3>& sourceVertices = mesh.Vertices();
		std::vector<XMFLOAT3>* textureCoordinates = mesh.TextureCoordinates().at( 0 );
		assert( textureCoordinates->size() == sourceVertices.size() );
		const std::vector<XMFLOAT3>& normals = mesh.Normals();
		assert( normals.size() == sourceVertices.size() );
		const std::vector<BoneVertexWeights>& boneWeights = mesh.BoneWeights();
		assert( boneWeights.size() == sourceVertices.size() );

		std::vector<VertexSkinnedPositionTextureNormal> vertices;
		vertices.reserve( sourceVertices.size() );
		for ( UINT i = 0; i < sourceVertices.size(); i++ )
		{
			XMFLOAT3 position = sourceVertices.at( i );
			XMFLOAT3 uv = textureCoordinates->at( i );
			XMFLOAT3 normal = normals.at( i );
			BoneVertexWeights vertexWeights = boneWeights.at( i );

			float weights[BoneVertexWeights::MaxBoneWeightsPerVertex];
			UINT indices[BoneVertexWeights::MaxBoneWeightsPerVertex];
			ZeroMemory( weights, sizeof( float ) * ARRAYSIZE( weights ) );
			ZeroMemory( indices, sizeof( UINT ) * ARRAYSIZE( indices ) );
			for ( UINT i = 0; i < vertexWeights.Weights().size(); i++ )
			{
				BoneVertexWeights::VertexWeight vertexWeight = vertexWeights.Weights().at( i );
				weights[i] = vertexWeight.Weight;
				indices[i] = vertexWeight.BoneIndex;
			}

			vertices.push_back( VertexSkinnedPositionTextureNormal( XMFLOAT4( position.x, position.y, position.z, 1.0f ), XMFLOAT2( uv.x, uv.y ), normal, XMUINT4( indices ), XMFLOAT4( weights ) ) );
		}

		CreateVertexBuffer( device, &vertices[0], vertices.size(), vertexBuffer );
	}

	void DirectionalLightSkinnedModelMaterial::CreateVertexBuffer( ID3D11Device* device, VertexSkinnedPositionTextureNormal* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer ) const
	{
		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory( &vertexBufferDesc, sizeof( vertexBufferDesc ) );
		vertexBufferDesc.ByteWidth = VertexSize() * vertexCount;
		vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexSubResourceData;
		ZeroMemory( &vertexSubResourceData, sizeof( vertexSubResourceData ) );
		vertexSubResourceData.pSysMem = vertices;
		if ( FAILED( device->CreateBuffer( &vertexBufferDesc, &vertexSubResourceData, vertexBuffer ) ) )
		{
			throw GameException( "ID3D11Device::CreateBuffer() failed." );
		}
	}

	UINT DirectionalLightSkinnedModelMaterial::VertexSize() const
	{
		return sizeof( VertexSkinnedPositionTextureNormal );
	}
}