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

using namespace Library;

namespace Rendering
{
	class UltimateSkinnedModelMaterial : public Material
	{
		RTTI_DECLARATIONS( UltimateSkinnedModelMaterial, Material )

		typedef struct _DirLightVariables
		{
			Variable Color;
			Variable Direction;

			_DirLightVariables(const Variable& color, const Variable& direction) 
				: Color( color ), Direction( direction ) { }
		} DirLightVariables;
	public:
		typedef struct _PointLightVariables
		{
			Variable Position;
			Variable Color;
			Variable Radius;

			_PointLightVariables( const Variable& position, const Variable& lightRadius, const Variable& color )
				: Position( position ), Radius( lightRadius ), Color( color ) { }
		} PointLightVariables;
		typedef struct _SpotLightVariables
		{
			Variable Position;
			Variable Color;
			Variable Radius;
			Variable Direction;
			Variable InnerAngle;
			Variable OuterAngle;

			_SpotLightVariables( const Variable& position, const Variable& lightRadius, const Variable& color, const Variable& direction, const Variable& innerAngle, const Variable& outerAngle )
				: Position( position ), Radius( lightRadius ), Color( color ), Direction( direction ), InnerAngle( innerAngle ), OuterAngle( outerAngle ) { }
		} SpotLightVariables;

		MATERIAL_VARIABLE_DECLARATION( WorldViewProjection )
		MATERIAL_VARIABLE_DECLARATION( World )
		MATERIAL_VARIABLE_DECLARATION( SpecularColor )
		MATERIAL_VARIABLE_DECLARATION( SpecularPower )
		MATERIAL_VARIABLE_DECLARATION( AmbientColor )
		MATERIAL_VARIABLE_DECLARATION( LightColor )
		MATERIAL_VARIABLE_DECLARATION( LightPosition )
		MATERIAL_VARIABLE_DECLARATION( LightRadius )
		//MATERIAL_VARIABLE_DECLARATION( LightDirection )
		//MATERIAL_VARIABLE_DECLARATION( SpotLightInnerAngle )
		//MATERIAL_VARIABLE_DECLARATION( SpotLightOuterAngle )
		MATERIAL_VARIABLE_DECLARATION( CameraPosition )
		MATERIAL_VARIABLE_DECLARATION( BoneTransforms )
		MATERIAL_VARIABLE_DECLARATION( ColorTexture )

	private:
		std::vector<DirLightVariables> mDirLights;
		std::vector<SpotLightVariables> mSpotLights;
		std::vector<PointLightVariables> mPointLights;

	public:
		UltimateSkinnedModelMaterial();
		int numPointLights = 0;
		int numSpotLights = 0;
		int numDirLights = 0;
		bool inited = false;

		std::vector<PointLightVariables*> PointLights;

		virtual void Initialize( Effect& effect ) override;
		virtual void CreateVertexBuffer( ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer ) const override;
		void CreateVertexBuffer( ID3D11Device* device, VertexSkinnedPositionTextureNormal* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer ) const;
		virtual UINT VertexSize() const override;
	};
}