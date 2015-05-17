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
#include "BasicMaterial.h"
#include "GameException.h"
#include "Mesh.h"
#include "ColorHelper.h"

namespace Library
{
    RTTI_DEFINITIONS(BasicMaterial)	

    BasicMaterial::BasicMaterial()
        : Material("main11"),
          MATERIAL_VARIABLE_INITIALIZATION(WorldViewProjection)
    {
    }

    MATERIAL_VARIABLE_DEFINITION(BasicMaterial, WorldViewProjection)

    void BasicMaterial::Initialize(Effect& effect)
    {
        Material::Initialize(effect);

        MATERIAL_VARIABLE_RETRIEVE(WorldViewProjection)

        D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        CreateInputLayout("main11", "p0", inputElementDescriptions, ARRAYSIZE(inputElementDescriptions));
    }

    void BasicMaterial::CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const
    {
        const std::vector<XMFLOAT3>& sourceVertices = mesh.Vertices();

        std::vector<VertexPositionColor> vertices;
        vertices.reserve(sourceVertices.size());
        if (mesh.VertexColors().size() > 0)
        {
            std::vector<XMFLOAT4>* vertexColors = mesh.VertexColors().at(0);
            assert(vertexColors->size() == sourceVertices.size());
            
            for (UINT i = 0; i < sourceVertices.size(); i++)
            {
                XMFLOAT3 position = sourceVertices.at(i);
                XMFLOAT4 color = vertexColors->at(i);
                vertices.push_back(VertexPositionColor(XMFLOAT4(position.x, position.y, position.z, 1.0f), color));
            }
        }
        else
        {
            XMFLOAT4 color = XMFLOAT4(reinterpret_cast<const float*>(&ColorHelper::White));
            for (UINT i = 0; i < sourceVertices.size(); i++)
            {
                XMFLOAT3 position = sourceVertices.at(i);
                vertices.push_back(VertexPositionColor(XMFLOAT4(position.x, position.y, position.z, 1.0f), color));
            }
        }

        CreateVertexBuffer(device, &vertices[0], vertices.size(), vertexBuffer);
    }

    void BasicMaterial::CreateVertexBuffer(ID3D11Device* device, VertexPositionColor* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer) const
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

    UINT BasicMaterial::VertexSize() const
    {
        return sizeof(VertexPositionColor);
    }
}