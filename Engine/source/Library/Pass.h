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
    class Technique;

    class Pass
    {
    public:
        Pass(Game& game, Technique& technique, ID3DX11EffectPass* pass);

        Technique& GetTechnique();
        ID3DX11EffectPass* GetPass() const;
        const D3DX11_PASS_DESC& PassDesc() const;
        const std::string& Name() const;

        void CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* inputElementDesc, UINT numElements,  ID3D11InputLayout **inputLayout);
        void Apply(UINT flags, ID3D11DeviceContext* context);

    private:
        Pass(const Pass& rhs);
        Pass& operator=(const Pass& rhs);

        Game& mGame;
        Technique& mTechnique;
        ID3DX11EffectPass* mPass;
        D3DX11_PASS_DESC mPassDesc;
        std::string mName;
    };
}