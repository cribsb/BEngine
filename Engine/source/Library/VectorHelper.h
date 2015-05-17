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
	class Vector2Helper
	{
	public:
		static const XMFLOAT2 Zero;
		static const XMFLOAT2 One;

		static std::string ToString(const XMFLOAT2& vector);

	private:
		Vector2Helper();
		Vector2Helper(const Vector2Helper& rhs);
		Vector2Helper& operator=(const Vector2Helper& rhs);
	};

	class Vector3Helper
	{
	public:
		static const XMFLOAT3 Zero;
		static const XMFLOAT3 One;
		static const XMFLOAT3 Forward;
		static const XMFLOAT3 Backward;
		static const XMFLOAT3 Up;
		static const XMFLOAT3 Down;
		static const XMFLOAT3 Right;
		static const XMFLOAT3 Left;

		static std::string ToString(const XMFLOAT3& vector);

	private:
		Vector3Helper();
		Vector3Helper(const Vector3Helper& rhs);
		Vector3Helper& operator=(const Vector3Helper& rhs);
	};

	class Vector4Helper
	{
	public:
		static const XMFLOAT4 Zero;
		static const XMFLOAT4 One;

		static std::string ToString(const XMFLOAT4& vector);

	private:
		Vector4Helper();
		Vector4Helper(const Vector3Helper& rhs);
		Vector4Helper& operator=(const Vector3Helper& rhs);
	};
}