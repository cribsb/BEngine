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
	class MathHelper
	{
	public:
		static float Clamp(float value, float min, float max);
		static float Saturate(float value);
		static UINT Saturate(UINT value);
	};

	inline float MathHelper::Clamp(float value, float min, float max)
	{
		return value < min ? min : (value > max ? max : value);
	}

	inline float MathHelper::Saturate(float value)
	{
		return value < 0.0f ? 0.0f : (value > 1.0f ? 1.0f : value);
	}

	inline UINT MathHelper::Saturate(UINT value)
	{
		return value < 0 ? 0 : (value > 255 ? 255 : value);
	}
}
