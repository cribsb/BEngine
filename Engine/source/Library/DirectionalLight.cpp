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
#include "DirectionalLight.h"
#include "VectorHelper.h"

namespace Library
{
	RTTI_DEFINITIONS(DirectionalLight)

	DirectionalLight::DirectionalLight(Game& game)
		: Light(game), mDirection(Vector3Helper::Forward), mUp(Vector3Helper::Up), mRight(Vector3Helper::Right)
	{
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	const XMFLOAT3& DirectionalLight::Direction() const
	{
		return mDirection;
	}
	
	const XMFLOAT3& DirectionalLight::Up() const
	{
		return mUp;
	}

	const XMFLOAT3& DirectionalLight::Right() const
	{
		return mRight;
	}

	XMVECTOR DirectionalLight::DirectionVector() const
	{
		return XMLoadFloat3(&mDirection);
	}

	XMVECTOR DirectionalLight::UpVector() const
	{
		return XMLoadFloat3(&mUp);
	}
	
	XMVECTOR DirectionalLight::RightVector() const
	{
		return XMLoadFloat3(&mRight);
	}

	void DirectionalLight::ApplyRotation(CXMMATRIX transform)
    {
        XMVECTOR direction = XMLoadFloat3(&mDirection);
        XMVECTOR up = XMLoadFloat3(&mUp);
        
        direction = XMVector3TransformNormal(direction, transform);
        direction = XMVector3Normalize(direction);

        up = XMVector3TransformNormal(up, transform);
        up = XMVector3Normalize(up);

        XMVECTOR right = XMVector3Cross(direction, up);
        up = XMVector3Cross(right, direction);

        XMStoreFloat3(&mDirection, direction);
        XMStoreFloat3(&mUp, up);
        XMStoreFloat3(&mRight, right);
    }

    void DirectionalLight::ApplyRotation(const XMFLOAT4X4& transform)
    {
        XMMATRIX transformMatrix = XMLoadFloat4x4(&transform);
        ApplyRotation(transformMatrix);
    }
}