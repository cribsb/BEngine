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
#include "SceneNode.h"

namespace Library
{
	class BoneVertexWeights
	{
	public:
		typedef struct _VertexWeight
		{
			float Weight;
			UINT BoneIndex;

			_VertexWeight(float weight, UINT boneIndex)
				: Weight(weight), BoneIndex(boneIndex) { }
		} VertexWeight;
		
		const std::vector<VertexWeight>& Weights();

		void AddWeight(float weight, UINT boneIndex);

		static const UINT MaxBoneWeightsPerVertex = 4U;

	private:
		std::vector<VertexWeight> mWeights;
	};

    class Bone : public SceneNode
    {
		RTTI_DECLARATIONS(Bone, SceneNode)

    public:	
		UINT Index() const;
		void SetIndex(UINT index);

		const XMFLOAT4X4& OffsetTransform() const;
		XMMATRIX OffsetTransformMatrix() const;

		Bone(const std::string& name, UINT index, const XMFLOAT4X4& offsetTransform);

    private:
		Bone();
        Bone(const Bone& rhs);
        Bone& operator=(const Bone& rhs);

		UINT mIndex;					// Index into the model's bone container
		XMFLOAT4X4 mOffsetTransform;	// Transforms from mesh space to bone space
    };
}
