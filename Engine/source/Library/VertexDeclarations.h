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
	typedef struct _VertexPosition
    {
        XMFLOAT4 Position;

        _VertexPosition() { }

		_VertexPosition(const XMFLOAT4& position)
            : Position(position) { }
    } VertexPosition;

	typedef struct _VertexPositionColor
    {
        XMFLOAT4 Position;
        XMFLOAT4 Color;

        _VertexPositionColor() { }

		_VertexPositionColor(const XMFLOAT4& position, const XMFLOAT4& color)
            : Position(position), Color(color) { }
    } VertexPositionColor;

	typedef struct _VertexPositionTexture
	{
		XMFLOAT4 Position;
		XMFLOAT2 TextureCoordinates;

		_VertexPositionTexture() { }

		_VertexPositionTexture(const XMFLOAT4& position, const XMFLOAT2& textureCoordinates)
			: Position(position), TextureCoordinates(textureCoordinates) { }
	} VertexPositionTexture;

	typedef struct _VertexPositionNormal
    {
        XMFLOAT4 Position;
        XMFLOAT3 Normal;

        _VertexPositionNormal() { }

		_VertexPositionNormal(const XMFLOAT4& position, const XMFLOAT3& normal)
            : Position(position), Normal(normal) { }
    } VertexPositionNormal;

	typedef struct _VertexPositionTextureNormal
	{
		XMFLOAT4 Position;
		XMFLOAT2 TextureCoordinates;
		XMFLOAT3 Normal;

		_VertexPositionTextureNormal() { }

		_VertexPositionTextureNormal(const XMFLOAT4& position, const XMFLOAT2& textureCoordinates, const XMFLOAT3& normal)
			: Position(position), TextureCoordinates(textureCoordinates), Normal(normal) { }
	} VertexPositionTextureNormal;

	typedef struct _VertexSkinnedPositionTextureNormal
	{
		XMFLOAT4 Position;
		XMFLOAT2 TextureCoordinates;
		XMFLOAT3 Normal;
		XMUINT4 BoneIndices;
		XMFLOAT4 BoneWeights;

		_VertexSkinnedPositionTextureNormal() { }

		_VertexSkinnedPositionTextureNormal(const XMFLOAT4& position, const XMFLOAT2& textureCoordinates, const XMFLOAT3& normal, const XMUINT4& boneIndices, const XMFLOAT4& boneWeights)
			: Position(position), TextureCoordinates(textureCoordinates), Normal(normal), BoneIndices(boneIndices), BoneWeights(boneWeights) { }
	} VertexSkinnedPositionTextureNormal;
}
