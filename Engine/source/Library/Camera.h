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

    class Camera : public GameComponent
    {
        RTTI_DECLARATIONS(Camera, GameComponent)

    public:
        Camera(Game& game);
        Camera(Game& game, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);

        virtual ~Camera();

        const XMFLOAT3& Position() const;
        const XMFLOAT3& Direction() const;
        const XMFLOAT3& Up() const;
        const XMFLOAT3& Right() const;
        
        XMVECTOR PositionVector() const;
        XMVECTOR DirectionVector() const;
        XMVECTOR UpVector() const;
        XMVECTOR RightVector() const;
        
        float AspectRatio() const;
        float FieldOfView() const;
        float NearPlaneDistance() const;
        float FarPlaneDistance() const;

        XMMATRIX ViewMatrix() const;
        XMMATRIX ProjectionMatrix() const;
        XMMATRIX ViewProjectionMatrix() const;

        virtual void SetPosition(FLOAT x, FLOAT y, FLOAT z);
        virtual void SetPosition(FXMVECTOR position);
        virtual void SetPosition(const XMFLOAT3& position);

        virtual void Reset();
        virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
        virtual void UpdateViewMatrix();
        virtual void UpdateProjectionMatrix();
        virtual void ApplyRotation(CXMMATRIX transform);
        virtual void ApplyRotation(const XMFLOAT4X4& transform);

        static const float DefaultFieldOfView;
        static const float DefaultNearPlaneDistance;
        static const float DefaultFarPlaneDistance;

    protected:
        float mFieldOfView;
        float mAspectRatio;		
        float mNearPlaneDistance;
        float mFarPlaneDistance;

        XMFLOAT3 mPosition;
        XMFLOAT3 mDirection;
        XMFLOAT3 mUp;
        XMFLOAT3 mRight;

        XMFLOAT4X4 mViewMatrix;
        XMFLOAT4X4 mProjectionMatrix;

    private:
        Camera(const Camera& rhs);
        Camera& operator=(const Camera& rhs);
    };
}

