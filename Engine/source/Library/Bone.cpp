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
#include "Bone.h"
#include "Model.h"
#include "GameException.h"
#include "MatrixHelper.h"
#include <assimp/scene.h>

namespace Library
{
	const std::vector<BoneVertexWeights::VertexWeight>& BoneVertexWeights::Weights()
	{
		return mWeights;
	}

	void BoneVertexWeights::AddWeight(float weight, UINT boneIndex)
	{
		if (mWeights.size() == MaxBoneWeightsPerVertex)
		{
			throw GameException("Maximum number of bone weights per vertex exceeded.");
		}

		mWeights.push_back(VertexWeight(weight, boneIndex));
	}

	RTTI_DEFINITIONS(Bone)

	Bone::Bone(const std::string& name, UINT index, const XMFLOAT4X4& offsetTransform)
	   : SceneNode(name), mIndex(index), mOffsetTransform(offsetTransform)
    {
    }

	UINT Bone::Index() const
	{
		return mIndex;
	}

	void Bone::SetIndex(UINT index)
	{
		mIndex = index;
	}

	const XMFLOAT4X4& Bone::OffsetTransform() const
	{
		return mOffsetTransform;
	}

	XMMATRIX Bone::OffsetTransformMatrix() const
	{
		return XMLoadFloat4x4(&mOffsetTransform);
	}
}
