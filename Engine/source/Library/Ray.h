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
    class Ray
    {
    public:
        Ray(FXMVECTOR position, FXMVECTOR direction);
		Ray(const XMFLOAT3& position, const XMFLOAT3& direction);
		
		const XMFLOAT3& Position() const;
        const XMFLOAT3& Direction() const;

		XMVECTOR PositionVector() const;
        XMVECTOR DirectionVector() const;

		virtual void SetPosition(float x, float y, float z);
        virtual void SetPosition(FXMVECTOR position);
        virtual void SetPosition(const XMFLOAT3& position);

		virtual void SetDirection(float x, float y, float z);
        virtual void SetDirection(FXMVECTOR direction);
        virtual void SetDirection(const XMFLOAT3& direction);
    
	private:
		Ray();

		XMFLOAT3 mPosition;
		XMFLOAT3 mDirection;
    };
}

