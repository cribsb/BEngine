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
#include "Pass.h"
#include "Game.h"
#include "GameException.h"

namespace Library
{
	Pass::Pass(Game& game, Technique& technique, ID3DX11EffectPass* pass)
		: mGame(game), mTechnique(technique), mPass(pass), mPassDesc(), mName()
	{
		mPass->GetDesc(&mPassDesc);
		mName = mPassDesc.Name;
	}
	
	Technique& Pass::GetTechnique()
	{
		return mTechnique;
	}

	ID3DX11EffectPass* Pass::GetPass() const
	{
		return mPass;
	}

	const D3DX11_PASS_DESC& Pass::PassDesc() const
	{
		return mPassDesc;
	}

	const std::string& Pass::Name() const
	{
		return mName;
	}

	void Pass::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* inputElementDesc, UINT numElements,  ID3D11InputLayout **inputLayout)
	{
		HRESULT hr = mGame.Direct3DDevice()->CreateInputLayout(inputElementDesc, numElements, mPassDesc.pIAInputSignature, mPassDesc.IAInputSignatureSize, inputLayout);
		if (FAILED(hr))
		{
			throw GameException("ID3D11Device::CreateInputLayout() failed.", hr);
		}
	}

	void Pass::Apply(UINT flags, ID3D11DeviceContext* context)
	{
		mPass->Apply(flags, context);
	}
}