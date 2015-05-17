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
#pragma once

#include "Common.h"
#include "Material.h"
#include "VertexDeclarations.h"

namespace Library
{
	class DistortionMappingMaterial : public Material
	{
		RTTI_DECLARATIONS(Material, DistortionMappingMaterial)
		
		MATERIAL_VARIABLE_DECLARATION(WorldViewProjection)
		MATERIAL_VARIABLE_DECLARATION(SceneTexture)
		MATERIAL_VARIABLE_DECLARATION(DistortionMap)
		MATERIAL_VARIABLE_DECLARATION(DisplacementScale)
		MATERIAL_VARIABLE_DECLARATION(Time)

	public:
		DistortionMappingMaterial();

		virtual void Initialize(Effect& effect) override;		
        virtual void CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const override;
        void CreateVertexBuffer(ID3D11Device* device, VertexPositionTexture* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer) const;
        virtual UINT VertexSize() const override;
	};
}

