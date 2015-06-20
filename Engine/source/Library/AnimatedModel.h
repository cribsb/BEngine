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

#include "DrawableGameComponent.h"
#include "RenderStateHelper.h"
#include "LuaScript.h"
#include "../..\BulletPhysics/src/btBulletDynamicsCommon.h"

class LuaScript;

using namespace Library;

namespace Library
{
	class Keyboard;
	class PointLight;
	class ProxyModel;
    class Effect;
	class SkinnedModelMaterial;
	class Model;
	class AnimationPlayer;
	class ColorHelper;
}

namespace DirectX
{
	class SpriteBatch;
	class SpriteFont;
}

namespace Rendering
{
    class AnimatedModel : public DrawableGameComponent
    {
        RTTI_DECLARATIONS(AnimatedModel, DrawableGameComponent)

    public:
        AnimatedModel(Game& game, Camera& camera);
        ~AnimatedModel();

		virtual void Initialize(LuaScript* s, btDiscreteDynamicsWorld* world, std::vector<GameComponent*> Components, XMCOLOR ambientColor = XMCOLOR(1.0f,1.0f,1.0f,1.0f));
		virtual void Update(const GameTime& gameTime) override;
        virtual void Draw(const GameTime& gameTime) override;
		XMFLOAT4X4 getWorldMatrix();

    private:
		std::vector<GameComponent*> mComponents;
		int mLightType = 0;

        AnimatedModel();
        AnimatedModel(const AnimatedModel& rhs);
        AnimatedModel& operator=(const AnimatedModel& rhs);	

		//void UpdateOptions();
		//void UpdateAmbientLight(const GameTime& gameTime);
		//void UpdatePointLight(const GameTime& gameTime);
		//void UpdateSpecularLight(const GameTime& gameTime);

		static const float LightModulationRate;
		static const float LightMovementRate;

        Effect* mEffect;
		SkinnedModelMaterial* mMaterial;

		Keyboard* mKeyboard;
		XMCOLOR mAmbientColor;
		//PointLight* mPointLight;
		XMVECTOR mColorVector;
		XMVECTOR mLightPositionVector;
		XMCOLOR mSpecularColor;
		float mSpecularPower;
        XMFLOAT4X4 mWorldMatrix;

		std::vector<ID3D11Buffer*> mVertexBuffers;
		std::vector<ID3D11Buffer*> mIndexBuffers;
		std::vector<UINT> mIndexCounts;
		std::vector<ID3D11ShaderResourceView*> mColorTextures;

		Model* mSkinnedModel;
		AnimationPlayer* mAnimationPlayer;		

		RenderStateHelper mRenderStateHelper;
		//ProxyModel* mProxyModel;
		//SpriteBatch* mSpriteBatch;
		//SpriteFont* mSpriteFont;
		//XMFLOAT2 mTextPosition;
		bool mManualAdvanceMode;

		float mXOffset;
		float mYOffset;
		float mZOffset;
		btMotionState* motionState;
    };
}
