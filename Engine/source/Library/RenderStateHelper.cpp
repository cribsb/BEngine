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
#include "RenderStateHelper.h"
#include "Game.h"

namespace Library
{
    RenderStateHelper::RenderStateHelper(Game& game)
        : mGame(game), mRasterizerState(nullptr), mBlendState(nullptr), mBlendFactor(new FLOAT[4]), mSampleMask(UINT_MAX), mDepthStencilState(nullptr), mStencilRef(UINT_MAX)
    {
    }

    RenderStateHelper::~RenderStateHelper()
    {
        ReleaseObject(mRasterizerState);
        ReleaseObject(mBlendState);
        ReleaseObject(mDepthStencilState);
        DeleteObjects(mBlendFactor);
    }

    void RenderStateHelper::ResetAll(ID3D11DeviceContext* deviceContext)
    {
        deviceContext->RSSetState(nullptr);
        deviceContext->OMSetBlendState(nullptr, nullptr, UINT_MAX);
        deviceContext->OMSetDepthStencilState(nullptr, UINT_MAX);
    }

	ID3D11RasterizerState* RenderStateHelper::RasterizerState()
	{
		return mRasterizerState;
	}

    ID3D11BlendState* RenderStateHelper::BlendState()
	{
		return mBlendState;
	}

    ID3D11DepthStencilState* RenderStateHelper::DepthStencilState()
	{
		return mDepthStencilState;
	}

    void RenderStateHelper::SaveRasterizerState()
    {
        ReleaseObject(mRasterizerState);
        mGame.Direct3DDeviceContext()->RSGetState(&mRasterizerState);
    }

    void RenderStateHelper::RestoreRasterizerState() const
    {
        mGame.Direct3DDeviceContext()->RSSetState(mRasterizerState);
    }

    void RenderStateHelper::SaveBlendState()
    {
        ReleaseObject(mBlendState);
        mGame.Direct3DDeviceContext()->OMGetBlendState(&mBlendState, mBlendFactor, &mSampleMask);
    }

    void RenderStateHelper::RestoreBlendState() const
    {
        mGame.Direct3DDeviceContext()->OMSetBlendState(mBlendState, mBlendFactor, mSampleMask);
    }

    void RenderStateHelper::SaveDepthStencilState()
    {
        ReleaseObject(mDepthStencilState);
        mGame.Direct3DDeviceContext()->OMGetDepthStencilState(&mDepthStencilState, &mStencilRef);
    }

    void RenderStateHelper::RestoreDepthStencilState() const
    {
        mGame.Direct3DDeviceContext()->OMSetDepthStencilState(mDepthStencilState, mStencilRef);
    }

    void RenderStateHelper::SaveAll()
    {
        SaveRasterizerState();
        SaveBlendState();
        SaveDepthStencilState();
    }

    void RenderStateHelper::RestoreAll() const
    {
        RestoreRasterizerState();
        RestoreBlendState();
        RestoreDepthStencilState();
    }
}
