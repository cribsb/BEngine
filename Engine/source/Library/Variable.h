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
    class Effect;

    class Variable
    {
    public:
        Variable(Effect& effect, ID3DX11EffectVariable* variable);

        Effect& GetEffect();
        ID3DX11EffectVariable* GetVariable() const;
        const D3DX11_EFFECT_VARIABLE_DESC& VariableDesc() const;
        ID3DX11EffectType* Type() const;
        const D3DX11_EFFECT_TYPE_DESC& TypeDesc() const;
        const std::string& Name() const;

        Variable& operator<<(CXMMATRIX value);
        Variable& operator<<(ID3D11ShaderResourceView* value);
        Variable& operator<<(FXMVECTOR value);
        Variable& operator<<(float value);
		Variable& operator<<(const std::vector<float>& values);
		Variable& operator<<(const std::vector<XMFLOAT2>& values);
		Variable& operator<<(const std::vector<XMFLOAT4X4>& values);

    private:
        Variable(const Variable& rhs);
        Variable& operator=(const Variable& rhs);

        Effect& mEffect;
        ID3DX11EffectVariable* mVariable;
        D3DX11_EFFECT_VARIABLE_DESC mVariableDesc;
        ID3DX11EffectType* mType;
        D3DX11_EFFECT_TYPE_DESC mTypeDesc;
        std::string mName;
    };
}