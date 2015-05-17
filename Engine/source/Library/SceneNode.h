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

namespace Library
{
	class SceneNode : public RTTI
	{
		RTTI_DECLARATIONS(SceneNode, RTTI)

	public:	
		const std::string& Name() const;
		SceneNode* Parent();
		std::vector<SceneNode*>& Children();
		const XMFLOAT4X4& Transform() const;
		XMMATRIX TransformMatrix() const;

		void SetParent(SceneNode* parent);

		void SetTransform(XMFLOAT4X4& transform);
		void SetTransform(CXMMATRIX transform);

		SceneNode(const std::string& name);
		SceneNode(const std::string& name, const XMFLOAT4X4& transform);

	protected:
		std::string mName;
		SceneNode* mParent;
		std::vector<SceneNode*> mChildren;
		XMFLOAT4X4 mTransform;

	private:
		SceneNode();
		SceneNode(const SceneNode& rhs);
		SceneNode& operator=(const SceneNode& rhs);
	};
}
