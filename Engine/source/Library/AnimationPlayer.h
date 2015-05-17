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

#include "GameComponent.h"

namespace Library
{
	class GameTime;
	class Model;
	class SceneNode;
	class AnimationClip;

    class AnimationPlayer : GameComponent
    {
		RTTI_DECLARATIONS(AnimationPlayer, GameComponent)

    public:        
		AnimationPlayer(Game& game, Model& model, bool interpolationEnabled = true);
		
		const Model& GetModel() const;
		const AnimationClip* CurrentClip() const;
		float CurrentTime() const;
		UINT CurrentKeyframe() const;
		const std::vector<XMFLOAT4X4>& BoneTransforms() const;
		
		bool InterpolationEnabled() const;
		bool IsPlayingClip() const;
		bool IsClipLooped() const;

		void SetInterpolationEnabled(bool interpolationEnabled);

		void StartClip(AnimationClip& clip);
		void PauseClip();
		void ResumeClip();
		virtual void Update(const GameTime& gameTime) override;
		void SetCurrentKeyFrame(UINT keyframe);

    private:
		AnimationPlayer();
        AnimationPlayer(const AnimationPlayer& rhs);
        AnimationPlayer& operator=(const AnimationPlayer& rhs);

		void GetBindPose(SceneNode& sceneNode);
		void GetBindPoseBottomUp(SceneNode& sceneNode);
		void GetPose(float time, SceneNode& sceneNode);
		void GetPoseAtKeyframe(UINT keyframe, SceneNode& sceneNode);
		void GetInterpolatedPose(float time, SceneNode& sceneNode);		

		Model* mModel;
		AnimationClip* mCurrentClip;
		float mCurrentTime;
		UINT mCurrentKeyframe;
		std::map<SceneNode*, XMFLOAT4X4> mToRootTransforms;
		std::vector<XMFLOAT4X4> mFinalTransforms;
		XMFLOAT4X4 mInverseRootTransform;
		bool mInterpolationEnabled;
		bool mIsPlayingClip;
		bool mIsClipLooped;
    };
}
