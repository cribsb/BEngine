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
#include "UltimateSkinnedModelMaterial.h"
#include "GameException.h"
#include "Mesh.h"
#include "Bone.h"

namespace Rendering
{
	RTTI_DEFINITIONS( UltimateSkinnedModelMaterial )

		UltimateSkinnedModelMaterial::UltimateSkinnedModelMaterial()
		: Material( "main11" ),
		MATERIAL_VARIABLE_INITIALIZATION( WorldViewProjection ),
		MATERIAL_VARIABLE_INITIALIZATION( World ),
		MATERIAL_VARIABLE_INITIALIZATION( SpecularColor ),
		MATERIAL_VARIABLE_INITIALIZATION( SpecularPower ),
		MATERIAL_VARIABLE_INITIALIZATION( AmbientColor ),
		MATERIAL_VARIABLE_INITIALIZATION( LightColor ),
		MATERIAL_VARIABLE_INITIALIZATION( LightPosition ),
		MATERIAL_VARIABLE_INITIALIZATION( LightRadius ),
		//MATERIAL_VARIABLE_INITIALIZATION( LightDirection ),
		//MATERIAL_VARIABLE_INITIALIZATION( SpotLightInnerAngle ),
		//MATERIAL_VARIABLE_INITIALIZATION( SpotLightOuterAngle ),
		MATERIAL_VARIABLE_INITIALIZATION( CameraPosition ),
		MATERIAL_VARIABLE_INITIALIZATION( BoneTransforms ),
		MATERIAL_VARIABLE_INITIALIZATION( ColorTexture )
	{ }

	MATERIAL_VARIABLE_DEFINITION( UltimateSkinnedModelMaterial, WorldViewProjection )
	MATERIAL_VARIABLE_DEFINITION( UltimateSkinnedModelMaterial, World )
	MATERIAL_VARIABLE_DEFINITION( UltimateSkinnedModelMaterial, SpecularColor )
	MATERIAL_VARIABLE_DEFINITION( UltimateSkinnedModelMaterial, SpecularPower )
	MATERIAL_VARIABLE_DEFINITION( UltimateSkinnedModelMaterial, AmbientColor )
	MATERIAL_VARIABLE_DEFINITION( UltimateSkinnedModelMaterial, LightColor )
	MATERIAL_VARIABLE_DEFINITION( UltimateSkinnedModelMaterial, LightPosition )
	MATERIAL_VARIABLE_DEFINITION( UltimateSkinnedModelMaterial, LightRadius )
	//MATERIAL_VARIABLE_DEFINITION( UltimateSkinnedModelMaterial, LightDirection )
	//MATERIAL_VARIABLE_DEFINITION( UltimateSkinnedModelMaterial, SpotLightInnerAngle )
	//MATERIAL_VARIABLE_DEFINITION( UltimateSkinnedModelMaterial, SpotLightOuterAngle )
	MATERIAL_VARIABLE_DEFINITION( UltimateSkinnedModelMaterial, CameraPosition )
	MATERIAL_VARIABLE_DEFINITION( UltimateSkinnedModelMaterial, BoneTransforms )
	MATERIAL_VARIABLE_DEFINITION( UltimateSkinnedModelMaterial, ColorTexture )

		void UltimateSkinnedModelMaterial::Initialize( Effect& effect )
	{
		Material::Initialize( effect );

		MATERIAL_VARIABLE_RETRIEVE( WorldViewProjection )
		MATERIAL_VARIABLE_RETRIEVE( World )
		MATERIAL_VARIABLE_RETRIEVE( SpecularColor )
		MATERIAL_VARIABLE_RETRIEVE( SpecularPower )
		MATERIAL_VARIABLE_RETRIEVE( AmbientColor )
		MATERIAL_VARIABLE_RETRIEVE( LightColor )
		MATERIAL_VARIABLE_RETRIEVE( LightPosition )
		MATERIAL_VARIABLE_RETRIEVE( LightRadius )
		//MATERIAL_VARIABLE_RETRIEVE( LightDirection )
		//MATERIAL_VARIABLE_RETRIEVE( SpotLightInnerAngle )
		//MATERIAL_VARIABLE_RETRIEVE( SpotLightOuterAngle )
		MATERIAL_VARIABLE_RETRIEVE( CameraPosition )
		MATERIAL_VARIABLE_RETRIEVE( BoneTransforms )
		MATERIAL_VARIABLE_RETRIEVE( ColorTexture )

		if ( inited )
		{
#if 0
			// PointLights
			Variable* pointLightsVariable = mEffect->VariablesByName().at( "PointLights" );
			mPointLights.reserve( pointLightsVariable->TypeDesc().Elements );
			for ( UINT i = 0; i < pointLightsVariable->TypeDesc().Elements; i++ )
			{
				Variable pointLightVariable = (*pointLightsVariable)[i];

				Variable position( *mEffect, pointLightVariable.GetVariable()->GetMemberByName( "Position" ) );
				//Variable lightRadius( *mEffect, pointLightVariable.GetVariable()->GetMemberByName( "Radius" ) );
				Variable lightRadius( *mEffect, pointLightVariable.GetVariable()->GetMemberByName( "Radius" ) );
				Variable color( *mEffect, pointLightVariable.GetVariable()->GetMemberByName( "Color" ) );

				numPointLights++;
				mPointLights.push_back( PointLightVariables( position, lightRadius, color ) );
			}
#endif // 0
		}
		// SpotLights
/*		Variable* spotLightsVariable = mEffect->VariablesByName().at( "SpotLights" );
		mSpotLights.reserve( spotLightsVariable->TypeDesc().Elements );
		for ( UINT i = 0; i < spotLightsVariable->TypeDesc().Elements; i++ )
		{
			Variable spotLightVariable = (spotLightsVariable)[i];

			Variable position( *mEffect, spotLightVariable.GetVariable()->GetMemberByName( "Position" ) );
			Variable lightRadius( *mEffect, spotLightVariable.GetVariable()->GetMemberByName( "LightRadius" ) );
			Variable color( *mEffect, spotLightVariable.GetVariable()->GetMemberByName( "Color" ) );
			Variable direction( *mEffect, spotLightVariable.GetVariable()->GetMemberByName( "Direction" ) );
			Variable innerAngle( *mEffect, spotLightVariable.GetVariable()->GetMemberByName( "InnerAngle" ) );
			Variable outerAngle( *mEffect, spotLightVariable.GetVariable()->GetMemberByName( "OuterAngle" ) );
			
			mSpotLights.push_back( SpotLightVariables( position, lightRadius, color, direction, innerAngle, outerAngle ) );
		}
		// DirectionalLights
		Variable* dirLightsVariable = mEffect->VariablesByName().at( "DirectionalLights" );
		mDirLights.reserve( dirLightsVariable->TypeDesc().Elements );
		for ( UINT i = 0; i < dirLightsVariable->TypeDesc().Elements; i++ )
		{
			Variable dirLightVariable = (dirLightsVariable)[i];

			Variable direction( *mEffect, dirLightVariable.GetVariable()->GetMemberByName( "Direction" ) );
			Variable color( *mEffect, dirLightVariable.GetVariable()->GetMemberByName( "Color" ) );

			mDirLights.push_back( DirLightVariables( direction, color ) );
		}*/

			D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEINDICES", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "WEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		//for ( int i = 0; i < numPointLights; i++ )
		//{
			CreateInputLayout( "main11", "p0", inputElementDescriptions, ARRAYSIZE( inputElementDescriptions ) );
			CreateInputLayout( "main11", "p4", inputElementDescriptions, ARRAYSIZE( inputElementDescriptions ) );
		//}
	}

	void UltimateSkinnedModelMaterial::CreateVertexBuffer( ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer ) const
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

	void UltimateSkinnedModelMaterial::CreateVertexBuffer( ID3D11Device* device, VertexSkinnedPositionTextureNormal* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer ) const
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

	UINT UltimateSkinnedModelMaterial::VertexSize() const
	{
		return sizeof( VertexSkinnedPositionTextureNormal );
	}
}