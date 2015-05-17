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
#include "Frustum.h"

namespace Library
{
    class BasicMaterial;
	class Pass;
	
    class RenderableFrustum : public DrawableGameComponent
    {
        RTTI_DECLARATIONS(RenderableFrustum, DrawableGameComponent)

    public:
        RenderableFrustum(Game& game, Camera& camera);
		RenderableFrustum(Game& game, Camera& camera, const XMFLOAT4& color);
        ~RenderableFrustum();

		const XMFLOAT3& Position() const;
        const XMFLOAT3& Direction() const;
        const XMFLOAT3& Up() const;
        const XMFLOAT3& Right() const;

		XMVECTOR PositionVector() const;
        XMVECTOR DirectionVector() const;
        XMVECTOR UpVector() const;
        XMVECTOR RightVector() const;

		void SetPosition(FLOAT x, FLOAT y, FLOAT z);
        void SetPosition(FXMVECTOR position);
        void SetPosition(const XMFLOAT3& position);

		void ApplyRotation(CXMMATRIX transform);
        void ApplyRotation(const XMFLOAT4X4& transform);

		void InitializeGeometry(const Frustum& frustum);

        virtual void Initialize() override;
        virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;

    private:
        RenderableFrustum();
        RenderableFrustum(const RenderableFrustum& rhs);
        RenderableFrustum& operator=(const RenderableFrustum& rhs);

		void InitializeVertexBuffer(const Frustum& frustum);
		void InitializeIndexBuffer();

		static const XMVECTORF32 DefaultColor;
		static const UINT FrustumVertexCount;		
		static const UINT FrustumPrimitiveCount;
		static const UINT FrustumIndicesPerPrimitive;
		static const UINT FrustumIndexCount;
		static const USHORT FrustumIndices[];

		ID3D11Buffer* mVertexBuffer;
        ID3D11Buffer* mIndexBuffer;
        BasicMaterial* mMaterial;
        Pass* mPass;
		ID3D11InputLayout* mInputLayout;
		
		XMFLOAT4 mColor;
		XMFLOAT3 mPosition;
		XMFLOAT3 mDirection;
        XMFLOAT3 mUp;
        XMFLOAT3 mRight;

		XMFLOAT4X4 mWorldMatrix;
    };
}