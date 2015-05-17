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
#include "Keyframe.h"
#include "VectorHelper.h"

namespace Library
{
	Keyframe::Keyframe(float time, const XMFLOAT3& translation, const XMFLOAT4& rotationQuaternion, const XMFLOAT3& scale)
		: mTime(time), mTranslation(translation), mRotationQuaternion(rotationQuaternion), mScale(scale)
    {
    }

	float Keyframe::Time() const
	{
		return mTime;
	}

	const XMFLOAT3& Keyframe::Translation() const
	{	
		return mTranslation;
	}

	const XMFLOAT4& Keyframe::RotationQuaternion() const
	{
		return mRotationQuaternion;
	}

	const XMFLOAT3& Keyframe::Scale() const
	{
		return mScale;
	}

	XMVECTOR Keyframe::TranslationVector() const
	{
		return XMLoadFloat3(&mTranslation);
	}

	XMVECTOR Keyframe::RotationQuaternionVector() const
	{
		return XMLoadFloat4(&mRotationQuaternion);
	}

	XMVECTOR Keyframe::ScaleVector() const
	{
		return XMLoadFloat3(&mScale);
	}

	XMMATRIX Keyframe::Transform() const
	{
		static XMVECTOR rotationOrigin = XMLoadFloat4(&Vector4Helper::Zero);

		return XMMatrixAffineTransformation(ScaleVector(), rotationOrigin, RotationQuaternionVector(), TranslationVector());
	}
}
