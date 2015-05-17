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
#include "Ray.h"

namespace Library
{
	enum FrustumPlane
	{
		FrustumPlaneNear = 0,
		FrustumPlaneFar,
		FrustumPlaneLeft,
		FrustumPlaneRight,
		FrustumPlaneTop,
		FrustumPlaneBottom
	};

    class Frustum
    {
    public:
        Frustum(CXMMATRIX matrix);
		
		const XMFLOAT4& Near() const;
		const XMFLOAT4& Far() const;
		const XMFLOAT4& Left() const;		
		const XMFLOAT4& Right() const;
		const XMFLOAT4& Top() const;
		const XMFLOAT4& Bottom() const;		

		XMVECTOR NearVector() const;
		XMVECTOR FarVector() const;
		XMVECTOR LeftVector() const;
		XMVECTOR RightVector() const;
		XMVECTOR TopVector() const;
		XMVECTOR BottomVector() const;
        
		const XMFLOAT3* Corners() const;

		XMMATRIX Matrix() const;
		void SetMatrix(CXMMATRIX matrix);
        void SetMatrix(const XMFLOAT4X4& matrix);
    
	private:
		Frustum();

		static Ray ComputeIntersectionLine(FXMVECTOR p1, FXMVECTOR p2);
		static XMVECTOR ComputeIntersection(FXMVECTOR& plane, Ray& ray);

        XMFLOAT4X4 mMatrix;
		XMFLOAT3 mCorners[8];
		XMFLOAT4 mPlanes[6];
    };
}

