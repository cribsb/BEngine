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
#include "SceneNode.h"
#include "MatrixHelper.h"

namespace Library
{
	RTTI_DEFINITIONS(SceneNode)

	SceneNode::SceneNode(const std::string& name)
		: mName(name), mParent(nullptr), mChildren(), mTransform(MatrixHelper::Identity)
	{
	}

	SceneNode::SceneNode(const std::string& name, const XMFLOAT4X4& transform)
		: mName(name), mParent(nullptr), mChildren(), mTransform(transform)
    {
    }

	const std::string& SceneNode::Name() const
	{
		return mName;
	}

	SceneNode* SceneNode::Parent()
	{
		return mParent;
	}

	std::vector<SceneNode*>& SceneNode::Children()
	{
		return mChildren;
	}

	const XMFLOAT4X4& SceneNode::Transform() const
	{
		return mTransform;
	}

	XMMATRIX SceneNode::TransformMatrix() const
	{
		return XMLoadFloat4x4(&mTransform);
	}

	void SceneNode::SetParent(SceneNode* parent)
	{
		mParent = parent;
	}

	void SceneNode::SetTransform(XMFLOAT4X4& transform)
	{
		mTransform = transform;
	}

	void SceneNode::SetTransform(CXMMATRIX transform)
	{
		XMFLOAT4X4 t;
		XMStoreFloat4x4(&t, transform);

		SetTransform(t);
	}
}
