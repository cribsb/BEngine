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
#include "DepthMapMaterial.h"
#include "GameException.h"
#include "Mesh.h"

namespace Library
{
    RTTI_DEFINITIONS(DepthMapMaterial)	

    DepthMapMaterial::DepthMapMaterial()
        : Material("create_depthmap"),
          MATERIAL_VARIABLE_INITIALIZATION(WorldLightViewProjection)
    {
    }

    MATERIAL_VARIABLE_DEFINITION(DepthMapMaterial, WorldLightViewProjection)

    void DepthMapMaterial::Initialize(Effect& effect)
    {
        Material::Initialize(effect);

        MATERIAL_VARIABLE_RETRIEVE(WorldLightViewProjection)

        D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        CreateInputLayout("create_depthmap", "p0", inputElementDescriptions, ARRAYSIZE(inputElementDescriptions));
		CreateInputLayout("create_depthmap_w_bias", "p0", inputElementDescriptions, ARRAYSIZE(inputElementDescriptions));
		CreateInputLayout("create_depthmap_w_render_target", "p0", inputElementDescriptions, ARRAYSIZE(inputElementDescriptions));		
    }

    void DepthMapMaterial::CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const
    {
        const std::vector<XMFLOAT3>& sourceVertices = mesh.Vertices();

        std::vector<VertexPosition> vertices;
        vertices.reserve(sourceVertices.size());
        for (UINT i = 0; i < sourceVertices.size(); i++)
        {
            XMFLOAT3 position = sourceVertices.at(i);
            vertices.push_back(VertexPosition(XMFLOAT4(position.x, position.y, position.z, 1.0f)));
        }

        CreateVertexBuffer(device, &vertices[0], vertices.size(), vertexBuffer);
    }

    void DepthMapMaterial::CreateVertexBuffer(ID3D11Device* device, VertexPosition* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer) const
    {
        D3D11_BUFFER_DESC vertexBufferDesc;
        ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
        vertexBufferDesc.ByteWidth = VertexSize() * vertexCount;
        vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;		
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA vertexSubResourceData;
        ZeroMemory(&vertexSubResourceData, sizeof(vertexSubResourceData));
        vertexSubResourceData.pSysMem = vertices;
        if (FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexSubResourceData, vertexBuffer)))
        {
            throw GameException("ID3D11Device::CreateBuffer() failed.");
        }
    }

    UINT DepthMapMaterial::VertexSize() const
    {
        return sizeof(VertexPosition);
    }
}