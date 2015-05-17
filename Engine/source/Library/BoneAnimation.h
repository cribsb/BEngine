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

struct aiNodeAnim;

namespace Library
{
	class Model;
	class Bone;
	class Keyframe;

    class BoneAnimation
    {
		friend class AnimationClip;

    public:        
        ~BoneAnimation();
		
		Bone& GetBone();
		const std::vector<Keyframe*> Keyframes() const;

		UINT GetTransform(float time, XMFLOAT4X4& transform) const;
		void GetTransformAtKeyframe(UINT keyframeIndex, XMFLOAT4X4& transform) const;
		void GetInteropolatedTransform(float time, XMFLOAT4X4& transform) const;		

    private:
		BoneAnimation(Model& model, aiNodeAnim& nodeAnim);

		BoneAnimation();
        BoneAnimation(const BoneAnimation& rhs);
        BoneAnimation& operator=(const BoneAnimation& rhs);

		UINT FindKeyframeIndex(float time) const;

		Model* mModel;
		Bone* mBone;
		std::vector<Keyframe*> mKeyframes;
    };
}
