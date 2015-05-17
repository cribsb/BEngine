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
    class RenderTarget : public RTTI
    {
		RTTI_DECLARATIONS(RenderTarget, RTTI)

    public:
        RenderTarget();
        virtual ~RenderTarget();

        virtual void Begin() = 0;
        virtual void End() = 0;

	protected:
		typedef struct _RenderTargetData
		{
			UINT ViewCount;
			ID3D11RenderTargetView** RenderTargetViews;
			ID3D11DepthStencilView* DepthStencilView;
			D3D11_VIEWPORT Viewport;
			
			_RenderTargetData(UINT viewCount, ID3D11RenderTargetView** renderTargetViews, ID3D11DepthStencilView* depthStencilView, const D3D11_VIEWPORT& viewport)
				: ViewCount(viewCount), RenderTargetViews(renderTargetViews), DepthStencilView(depthStencilView), Viewport(viewport) { }
		} RenderTargetData;

		void Begin(ID3D11DeviceContext* deviceContext, UINT viewCount, ID3D11RenderTargetView** renderTargetViews, ID3D11DepthStencilView* depthStencilView, const D3D11_VIEWPORT& viewport);
		void End(ID3D11DeviceContext* deviceContext);

	private:
        RenderTarget(const RenderTarget& rhs);
        RenderTarget& operator=(const RenderTarget& rhs);

		static std::stack<RenderTargetData> sRenderTargetStack;
    };
}