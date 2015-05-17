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
#include <random>

namespace Library
{
	class ColorHelper
	{
	public:
		static const XMVECTORF32 Black;
		static const XMVECTORF32 White;
		static const XMVECTORF32 Red;
		static const XMVECTORF32 Green;
		static const XMVECTORF32 Blue;
		static const XMVECTORF32 Yellow;
		static const XMVECTORF32 BlueGreen;
		static const XMVECTORF32 Purple;
		static const XMVECTORF32 CornflowerBlue;
		static const XMVECTORF32 Wheat;
		static const XMVECTORF32 LightGray;

		static XMFLOAT4 RandomColor();

	private:
		static std::random_device sDevice;
		static std::default_random_engine sGenerator;
		static std::uniform_real_distribution<float> sDistribution;

		ColorHelper();
		ColorHelper(const ColorHelper& rhs);
		ColorHelper& operator=(const ColorHelper& rhs);
	};
}