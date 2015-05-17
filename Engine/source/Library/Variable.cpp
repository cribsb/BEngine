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
#include "Variable.h"
#include "GameException.h"

namespace Library
{
	Variable::Variable(Effect& effect, ID3DX11EffectVariable* variable)
		: mEffect(effect), mVariable(variable), mVariableDesc(), mType(nullptr), mTypeDesc(), mName()
	{
		mVariable->GetDesc(&mVariableDesc);
		mName = mVariableDesc.Name;
		mType = mVariable->GetType();
		mType->GetDesc(&mTypeDesc);
	}

	Effect& Variable::GetEffect()
	{
		return mEffect;
	}
	
	ID3DX11EffectVariable* Variable::GetVariable() const
	{
		return mVariable;
	}

	const D3DX11_EFFECT_VARIABLE_DESC& Variable::VariableDesc() const
	{
		return mVariableDesc;
	}

	const D3DX11_EFFECT_TYPE_DESC& Variable::TypeDesc() const
	{
		return mTypeDesc;
	}

	ID3DX11EffectType* Variable::Type() const
	{
		return mType;
	}

	const std::string& Variable::Name() const
	{
		return mName;
	}

	Variable& Variable::operator<<(CXMMATRIX value)
	{
		ID3DX11EffectMatrixVariable* variable = mVariable->AsMatrix();
		if (variable->IsValid() == false)
		{
			throw GameException("Invalid effect variable cast.");
		}

		variable->SetMatrix(reinterpret_cast<const float*>(&value));
	
		return *this;
	}

	Variable& Variable::operator<<(ID3D11ShaderResourceView* value)
	{
		ID3DX11EffectShaderResourceVariable* variable = mVariable->AsShaderResource();
		if (variable->IsValid() == false)
		{
			throw GameException("Invalid effect variable cast.");
		}

		variable->SetResource(value);
	
		return *this;
	}

	Variable& Variable::operator<<(FXMVECTOR value)
	{
		ID3DX11EffectVectorVariable* variable = mVariable->AsVector();
		if (variable->IsValid() == false)
		{
			throw GameException("Invalid effect variable cast.");
		}

		variable->SetFloatVector(reinterpret_cast<const float*>(&value));
	
		return *this;
	}

	Variable& Variable::operator<<(float value)
	{
		ID3DX11EffectScalarVariable* variable = mVariable->AsScalar();
		if (variable->IsValid() == false)
		{
			throw GameException("Invalid effect variable cast.");
		}

		variable->SetFloat(value);
	
		return *this;
	}

	Variable& Variable::operator<<(const std::vector<float>& values)
	{
		ID3DX11EffectScalarVariable* variable = mVariable->AsScalar();
		if (variable->IsValid() == false)
		{
			throw GameException("Invalid effect variable cast.");
		}

		variable->SetFloatArray(&values[0], 0, values.size());
	
		return *this;
	}

	Variable& Variable::operator<<(const std::vector<XMFLOAT2>& values)
	{
		ID3DX11EffectVectorVariable* variable = mVariable->AsVector();
		if (variable->IsValid() == false)
		{
			throw GameException("Invalid effect variable cast.");
		}

		variable->SetFloatVectorArray(reinterpret_cast<const float*>(&values[0]), 0, values.size());
	
		return *this;
	}

	Variable& Variable::operator<<(const std::vector<XMFLOAT4X4>& values)
	{
		ID3DX11EffectMatrixVariable* variable = mVariable->AsMatrix();
		if (variable->IsValid() == false)
		{
			throw GameException("Invalid effect variable cast.");
		}

		variable->SetMatrixArray(reinterpret_cast<const float*>(&values[0]), 0, values.size());

		return *this;
	}
}