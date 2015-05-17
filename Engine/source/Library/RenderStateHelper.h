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
    class Game;

    class RenderStateHelper
    {
    public:
        RenderStateHelper(Game& game);
        ~RenderStateHelper();

        static void ResetAll(ID3D11DeviceContext* deviceContext);

        ID3D11RasterizerState* RasterizerState();
        ID3D11BlendState* BlendState();
        ID3D11DepthStencilState* DepthStencilState();

        void SaveRasterizerState();
        void RestoreRasterizerState() const;

        void SaveBlendState();
        void RestoreBlendState() const;

        void SaveDepthStencilState();
        void RestoreDepthStencilState() const;

        void SaveAll();
        void RestoreAll() const;

    private:
        RenderStateHelper(const RenderStateHelper& rhs);
        RenderStateHelper& operator=(const RenderStateHelper& rhs);

        Game& mGame;

        ID3D11RasterizerState* mRasterizerState;
        ID3D11BlendState* mBlendState;
        FLOAT* mBlendFactor;
        UINT mSampleMask;
        ID3D11DepthStencilState* mDepthStencilState;
        UINT mStencilRef;
    };
}
