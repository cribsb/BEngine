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
#include "SamplerStates.h"
#include "GameException.h"

namespace Library
{
	ID3D11SamplerState* SamplerStates::TrilinearWrap = nullptr;
	ID3D11SamplerState* SamplerStates::TrilinearMirror = nullptr;
	ID3D11SamplerState* SamplerStates::TrilinearClamp = nullptr;
	ID3D11SamplerState* SamplerStates::TrilinerBorder = nullptr;

	XMVECTORF32 SamplerStates::BorderColor = { 0.0f, 0.0f, 0.0f, 1.0f };

	void SamplerStates::Initialize(ID3D11Device* direct3DDevice)
	{
		assert(direct3DDevice != nullptr);

		D3D11_SAMPLER_DESC samplerStateDesc;
		ZeroMemory(&samplerStateDesc, sizeof(samplerStateDesc));
		samplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		
		HRESULT hr = direct3DDevice->CreateSamplerState(&samplerStateDesc, &TrilinearWrap);
		if (FAILED(hr))
		{
			throw GameException("ID3D11Device::CreateSamplerState() failed.", hr);
		}
		
		ZeroMemory(&samplerStateDesc, sizeof(samplerStateDesc));
		samplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
		samplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
		samplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;

		hr = direct3DDevice->CreateSamplerState(&samplerStateDesc, &TrilinearMirror);
		if (FAILED(hr))
		{
			throw GameException("ID3D11Device::CreateSamplerState() failed.", hr);
		}

		ZeroMemory(&samplerStateDesc, sizeof(samplerStateDesc));
		samplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		hr = direct3DDevice->CreateSamplerState(&samplerStateDesc, &TrilinearClamp);
		if (FAILED(hr))
		{
			throw GameException("ID3D11Device::CreateSamplerState() failed.", hr);
		}

		ZeroMemory(&samplerStateDesc, sizeof(samplerStateDesc));
		samplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		memcpy(samplerStateDesc.BorderColor, reinterpret_cast<FLOAT*>(&BorderColor), sizeof(FLOAT) * 4);

		hr = direct3DDevice->CreateSamplerState(&samplerStateDesc, &TrilinerBorder);
		if (FAILED(hr))
		{
			throw GameException("ID3D11Device::CreateSamplerState() failed.", hr);
		}
	}

	void SamplerStates::Release()
	{
		ReleaseObject(TrilinearWrap);
		ReleaseObject(TrilinearMirror);
		ReleaseObject(TrilinearClamp);
		ReleaseObject(TrilinerBorder);
	}
}