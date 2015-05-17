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

#include <functional>
#include "Common.h"
#include "DrawableGameComponent.h"

namespace Library
{
	class Effect;
	class BloomMaterial;
	class FullScreenRenderTarget;
	class FullScreenQuad;
	class GaussianBlur;

	typedef struct _BloomSettings
	{
		float BloomThreshold;
		float BlurAmount;
		float BloomIntensity;
		float BloomSaturation;
		float SceneIntensity;
		float SceneSaturation;
	} BloomSettings;

	enum BloomDrawMode
	{
		BloomDrawModeNormal = 0,
		BloomDrawModeExtractedTexture1,
		BloomDrawModeBlurredTexture,
		BloomDrawModeEnd
	};

	class Bloom : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(Bloom, DrawableGameComponent)

	public:
		Bloom(Game& game, Camera& camera);
		Bloom(Game& game, Camera& camera, const BloomSettings& bloomSettings);
		~Bloom();
		
		ID3D11ShaderResourceView* SceneTexture();
		void SetSceneTexture(ID3D11ShaderResourceView& sceneTexture);

		const BloomSettings& GetBloomSettings() const;
		void SetBloomSettings(const BloomSettings& bloomSettings);

		BloomDrawMode DrawMode() const;
		std::string DrawModeString() const;
		void SetDrawMode(BloomDrawMode drawMode);

		virtual void Initialize() override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		Bloom();
		Bloom(const Bloom& rhs);
		Bloom& operator=(const Bloom& rhs);

		void DrawNormal(const GameTime& gameTime);
		void DrawExtractedTexture(const GameTime& gameTime);
		void DrawBlurredTexture(const GameTime& gameTime);

		void UpdateBloomExtractMaterial();
		void UpdateBloomCompositeMaterial();
		void UpdateNoBloomMaterial();

		static const std::string DrawModeDisplayNames[];
		static const BloomSettings DefaultBloomSettings;		

		Effect* mBloomEffect;
		BloomMaterial* mBloomMaterial;
		ID3D11ShaderResourceView* mSceneTexture;
		FullScreenRenderTarget* mRenderTarget;
		FullScreenQuad* mFullScreenQuad;
		GaussianBlur* mGaussianBlur;
		BloomSettings mBloomSettings;
		BloomDrawMode mDrawMode;
		std::function<void(const GameTime& gameTime)> mDrawFunctions[BloomDrawModeEnd];
	};
}