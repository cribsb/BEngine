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
#include <sstream>
#include "VectorHelper.h"

namespace Library
{
	const XMFLOAT2 Vector2Helper::Zero = XMFLOAT2(0.0f, 0.0f);
	const XMFLOAT2 Vector2Helper::One = XMFLOAT2(1.0f, 1.0f);

	std::string Vector2Helper::ToString(const XMFLOAT2& vector)
	{
		std::stringstream stream;

		stream << "{" << vector.x << ", " << vector.y << "}";

		return stream.str();
	}

	const XMFLOAT3 Vector3Helper::Zero = XMFLOAT3(0.0f, 0.0f, 0.0f);
	const XMFLOAT3 Vector3Helper::One = XMFLOAT3(1.0f, 1.0f, 1.0f);
	const XMFLOAT3 Vector3Helper::Forward = XMFLOAT3(0.0f, 0.0f, -1.0f);
	const XMFLOAT3 Vector3Helper::Backward = XMFLOAT3(0.0f, 0.0f, 1.0f);
	const XMFLOAT3 Vector3Helper::Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	const XMFLOAT3 Vector3Helper::Down = XMFLOAT3(0.0f, -1.0f, 0.0f);
	const XMFLOAT3 Vector3Helper::Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	const XMFLOAT3 Vector3Helper::Left = XMFLOAT3(-1.0f, 0.0f, 0.0f);

	std::string Vector3Helper::ToString(const XMFLOAT3& vector)
	{
		std::stringstream stream;

		stream << "{" << vector.x << ", " << vector.y << ", " << vector.z << "}";

		return stream.str();
	}

	const XMFLOAT4 Vector4Helper::Zero = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	const XMFLOAT4 Vector4Helper::One = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	std::string Vector4Helper::ToString(const XMFLOAT4& vector)
	{
		std::stringstream stream;

		stream << "{" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << "}";

		return stream.str();
	}
}
