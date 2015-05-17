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
#include "RenderTarget.h"

namespace Library
{
    class Game;

    class DepthMap : public RenderTarget
    {
		RTTI_DECLARATIONS(DepthMap, RenderTarget)

    public:
        DepthMap(Game& game, UINT width, UINT height);
        ~DepthMap();

		ID3D11ShaderResourceView* OutputTexture() const;
		ID3D11DepthStencilView* DepthStencilView() const;
		
        virtual void Begin() override;
		virtual void End() override;

    private:
        DepthMap();
        DepthMap(const DepthMap& rhs);
        DepthMap& operator=(const DepthMap& rhs);

        Game* mGame;
		ID3D11DepthStencilView* mDepthStencilView;
		ID3D11ShaderResourceView* mOutputTexture;
		D3D11_VIEWPORT mViewport;
    };
}