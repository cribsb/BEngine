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
#include "DrawableGameComponent.h"

namespace Library
{
	class Effect;
	class Pass;
	class DistortionMappingMaterial;
	class FullScreenRenderTarget;
	class FullScreenQuad;
	class Mesh;

	enum DistortionTechnique
	{
		DistortionTechniqueDisplacement = 0,
		DistortionTechniqueEnd
	};

	class DistortionMapping : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(DistortionMapping, DrawableGameComponent)

	public:
		DistortionMapping(Game& game, Camera& camera);
		~DistortionMapping();

		DistortionTechnique GetDistortionTechnique() const;
		void SetDistortionTechnique(DistortionTechnique distortionTechnique);
		
		ID3D11ShaderResourceView* SceneTexture();
		void SetSceneTexture(ID3D11ShaderResourceView& sceneTexture);

		DistortionMappingMaterial* GetMaterial();

		virtual void Initialize() override;		
		virtual void Draw(const GameTime& gameTime) override;

		void BeginDistortionMap();
		void DrawMeshToDistortionMap(Mesh& mesh, CXMMATRIX worldMatrix);
		void EndDistortionMap();

	private:
		DistortionMapping();
		DistortionMapping(const DistortionMapping& rhs);
		DistortionMapping& operator=(const DistortionMapping& rhs);

		void UpdateDistortionCompositeMaterial();

		Effect* mDistortionEffect;
		DistortionMappingMaterial* mDistortionMappingMaterial;
		Pass* mDistortionPass;
		ID3D11InputLayout* mDistortionInputLayout;
		DistortionTechnique mDistortionTechnique;
		ID3D11ShaderResourceView* mSceneTexture;
		FullScreenRenderTarget* mRenderTarget;
		FullScreenQuad* mFullScreenQuad;
	};
}