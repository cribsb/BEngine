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
	class BasicMaterial;	
	class Pass;

	class Grid : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(Grid, DrawableGameComponent)

	public:
		Grid(Game& game, Camera& camera);
		Grid(Game& game, Camera& camera, UINT size, UINT scale, XMFLOAT4 color);
		~Grid();

		const XMFLOAT3& Position() const;
		const XMFLOAT4 Color() const;
		const UINT Size() const;
		const UINT Scale() const;

		void SetPosition(const XMFLOAT3& position);
		void SetPosition(float x, float y, float z);
		void SetColor(const XMFLOAT4& color);
		void SetSize(UINT size);
		void SetScale(UINT scale);

		virtual void Initialize() override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		Grid();
		Grid(const Grid& rhs);
		Grid& operator=(const Grid& rhs);
		
		void InitializeGrid();

		static const UINT DefaultSize;
		static const UINT DefaultScale;
		static const XMFLOAT4 DefaultColor;

		BasicMaterial* mMaterial;
		Pass* mPass;
		ID3D11InputLayout* mInputLayout;
		ID3D11Buffer* mVertexBuffer;
	
		XMFLOAT3 mPosition;
		UINT mSize;
		UINT mScale;
		XMFLOAT4 mColor;
		XMFLOAT4X4 mWorldMatrix;
	};
}