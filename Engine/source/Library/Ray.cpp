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
#include "Ray.h"

namespace Library
{
    Ray::Ray(FXMVECTOR position, FXMVECTOR direction)
		: mPosition(), mDirection()
	{
		XMStoreFloat3(&mPosition, position);
		XMStoreFloat3(&mDirection, direction);
	}

	Ray::Ray(const XMFLOAT3& position, const XMFLOAT3& direction)
		: mPosition(position), mDirection(direction)
	{
	}

	const XMFLOAT3& Ray::Position() const
    {
        return mPosition;
    }

    const XMFLOAT3& Ray::Direction() const
    {
        return mDirection;
    }

	XMVECTOR Ray::PositionVector() const
    {
        return XMLoadFloat3(&mPosition);
    }

    XMVECTOR Ray::DirectionVector() const
    {
        return XMLoadFloat3(&mDirection);
    }

	void Ray::SetPosition(FLOAT x, FLOAT y, FLOAT z)
    {
        XMVECTOR position = XMVectorSet(x, y, z, 1.0f);
        SetPosition(position);
    }

    void Ray::SetPosition(FXMVECTOR position)
    {
        XMStoreFloat3(&mPosition, position);
    }

    void Ray::SetPosition(const XMFLOAT3& position)
    {
        mPosition = position;
    }

	void Ray::SetDirection(FLOAT x, FLOAT y, FLOAT z)
    {
        XMVECTOR direction = XMVectorSet(x, y, z, 0.0f);
        SetDirection(direction);
    }

    void Ray::SetDirection(FXMVECTOR direction)
    {
        XMStoreFloat3(&mDirection, direction);
    }

    void Ray::SetDirection(const XMFLOAT3& direction)
    {
        mDirection = direction;
    }
}
