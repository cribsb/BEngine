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
    class Keyframe
    {
		friend class BoneAnimation;

    public:
		float Time() const;
		const XMFLOAT3& Translation() const;
		const XMFLOAT4& RotationQuaternion() const;
		const XMFLOAT3& Scale() const;

		XMVECTOR TranslationVector() const;
		XMVECTOR RotationQuaternionVector() const;
		XMVECTOR ScaleVector() const;

		XMMATRIX Transform() const;

    private:
		Keyframe(float time, const XMFLOAT3& translation, const XMFLOAT4& rotationQuaternion, const XMFLOAT3& scale);

		Keyframe();
        Keyframe(const Keyframe& rhs);
        Keyframe& operator=(const Keyframe& rhs);

		float mTime;
		XMFLOAT3 mTranslation;
		XMFLOAT4 mRotationQuaternion;
		XMFLOAT3 mScale;
    };
}
