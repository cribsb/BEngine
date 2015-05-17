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
#include "BloomMaterial.h"
#include "GameException.h"

namespace Library
{
	RTTI_DEFINITIONS(BloomMaterial)

	BloomMaterial::BloomMaterial()
		: PostProcessingMaterial(),
		  MATERIAL_VARIABLE_INITIALIZATION(BloomTexture), MATERIAL_VARIABLE_INITIALIZATION(BloomThreshold),
		  MATERIAL_VARIABLE_INITIALIZATION(BloomIntensity), MATERIAL_VARIABLE_INITIALIZATION(BloomSaturation),
		  MATERIAL_VARIABLE_INITIALIZATION(SceneIntensity), MATERIAL_VARIABLE_INITIALIZATION(SceneSaturation)
	{
	}

	MATERIAL_VARIABLE_DEFINITION(BloomMaterial, BloomTexture)
	MATERIAL_VARIABLE_DEFINITION(BloomMaterial, BloomThreshold)
	MATERIAL_VARIABLE_DEFINITION(BloomMaterial, BloomIntensity)
	MATERIAL_VARIABLE_DEFINITION(BloomMaterial, BloomSaturation)
	MATERIAL_VARIABLE_DEFINITION(BloomMaterial, SceneIntensity)
	MATERIAL_VARIABLE_DEFINITION(BloomMaterial, SceneSaturation)

	void BloomMaterial::Initialize(Effect& effect)
	{
		PostProcessingMaterial::Initialize(effect);

		MATERIAL_VARIABLE_RETRIEVE(BloomTexture)
		MATERIAL_VARIABLE_RETRIEVE(BloomThreshold)
		MATERIAL_VARIABLE_RETRIEVE(BloomIntensity)
		MATERIAL_VARIABLE_RETRIEVE(BloomSaturation)
		MATERIAL_VARIABLE_RETRIEVE(SceneIntensity)
		MATERIAL_VARIABLE_RETRIEVE(SceneSaturation)
	}
}