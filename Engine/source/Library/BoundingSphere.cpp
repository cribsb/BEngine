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
#include "BoundingSphere.h"

namespace Library
{
	BoundingSphere::BoundingSphere()
		: mCenter(0.0f, 0.0f, 0.0f), mRadius(0.0f)
	{
	}

    BoundingSphere::BoundingSphere(FXMVECTOR center, float radius)
		: mCenter(), mRadius(radius)
	{
		XMStoreFloat3(&mCenter, center);
	}

	BoundingSphere::BoundingSphere(const XMFLOAT3& center, float radius)
		: mCenter(center), mRadius(radius)
	{
	}

	XMFLOAT3& BoundingSphere::Center()
    {
        return mCenter;
    }

    float& BoundingSphere::Radius()
    {
        return mRadius;
    }
}
