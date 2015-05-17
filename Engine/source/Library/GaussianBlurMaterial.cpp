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
#include "GaussianBlurMaterial.h"
#include "GameException.h"

namespace Library
{
	RTTI_DEFINITIONS(GaussianBlurMaterial)

	GaussianBlurMaterial::GaussianBlurMaterial()
		: PostProcessingMaterial(),
		  MATERIAL_VARIABLE_INITIALIZATION(SampleOffsets), MATERIAL_VARIABLE_INITIALIZATION(SampleWeights)
	{
	}

	MATERIAL_VARIABLE_DEFINITION(GaussianBlurMaterial, SampleOffsets)
	MATERIAL_VARIABLE_DEFINITION(GaussianBlurMaterial, SampleWeights)

	void GaussianBlurMaterial::Initialize(Effect& effect)
	{
		PostProcessingMaterial::Initialize(effect);

		MATERIAL_VARIABLE_RETRIEVE(SampleOffsets)
		MATERIAL_VARIABLE_RETRIEVE(SampleWeights)
	}
}