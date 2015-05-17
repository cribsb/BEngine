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
	class MatrixHelper
	{
	public:
		static const XMFLOAT4X4 Identity;
		static const XMFLOAT4X4 Zero;

		static void GetForward(CXMMATRIX matrix, XMFLOAT3 &vector);
		static void GetUp(CXMMATRIX matrix, XMFLOAT3 &vector);
		static void GetRight(CXMMATRIX matrix, XMFLOAT3 &vector);
		static void GetTranslation(CXMMATRIX matrix, XMFLOAT3 &vector);

		static void SetForward(XMMATRIX& matrix, XMFLOAT3 &forward);
		static void SetUp(XMMATRIX& matrix, XMFLOAT3 &up);
		static void SetRight(XMMATRIX& matrix, XMFLOAT3 &right);
		static void SetTranslation(XMMATRIX& matrix, XMFLOAT3 &translation);

	private:
		MatrixHelper();
		MatrixHelper(const MatrixHelper& rhs);
		MatrixHelper& operator=(const MatrixHelper& rhs);
	};
}