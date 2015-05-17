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
#include "RenderTarget.h"
#include "Game.h"

namespace Library
{
    RTTI_DEFINITIONS(RenderTarget)

    std::stack<RenderTarget::RenderTargetData> RenderTarget::sRenderTargetStack;

    RenderTarget::RenderTarget()
    {
    }

    RenderTarget::~RenderTarget()
    {
    }

    void RenderTarget::Begin(ID3D11DeviceContext* deviceContext, UINT viewCount, ID3D11RenderTargetView** renderTargetViews, ID3D11DepthStencilView* depthStencilView, const D3D11_VIEWPORT& viewport)
    {
        sRenderTargetStack.push(RenderTargetData(viewCount, renderTargetViews, depthStencilView, viewport));
        deviceContext->OMSetRenderTargets(viewCount, renderTargetViews, depthStencilView);
        deviceContext->RSSetViewports(1, &viewport);
    }

    void RenderTarget::End(ID3D11DeviceContext* deviceContext)
    {
        sRenderTargetStack.pop();

        RenderTargetData renderTargetData = sRenderTargetStack.top();
        deviceContext->OMSetRenderTargets(renderTargetData.ViewCount, renderTargetData.RenderTargetViews, renderTargetData.DepthStencilView);
        deviceContext->RSSetViewports(1, &renderTargetData.Viewport);
    }
}