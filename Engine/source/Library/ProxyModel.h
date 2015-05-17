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
	class BasicMaterial;

	class ProxyModel : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(ProxyModel, DrawableGameComponent)

	public:
		ProxyModel(Game& game, Camera& camera, const std::string& modelFileName, float scale = 1.0f);
		~ProxyModel();

		const XMFLOAT3& Position() const;
        const XMFLOAT3& Direction() const;
        const XMFLOAT3& Up() const;
        const XMFLOAT3& Right() const;

		XMVECTOR PositionVector() const;
        XMVECTOR DirectionVector() const;
        XMVECTOR UpVector() const;
        XMVECTOR RightVector() const;

		bool& DisplayWireframe();

		void SetPosition(FLOAT x, FLOAT y, FLOAT z);
        void SetPosition(FXMVECTOR position);
        void SetPosition(const XMFLOAT3& position);

		void ApplyRotation(CXMMATRIX transform);
        void ApplyRotation(const XMFLOAT4X4& transform);

		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;		
		virtual void Draw(const GameTime& gameTime) override;

	private:
		ProxyModel();
		ProxyModel(const ProxyModel& rhs);
		ProxyModel& operator=(const ProxyModel& rhs);

		std::string mModelFileName;
		Effect* mEffect;
		BasicMaterial* mMaterial;
		ID3D11Buffer* mVertexBuffer;
		ID3D11Buffer* mIndexBuffer;
		UINT mIndexCount;
        
		XMFLOAT4X4 mWorldMatrix;
		XMFLOAT4X4 mScaleMatrix;

		bool mDisplayWireframe;
		XMFLOAT3 mPosition;
		XMFLOAT3 mDirection;
        XMFLOAT3 mUp;
        XMFLOAT3 mRight;
	};
}