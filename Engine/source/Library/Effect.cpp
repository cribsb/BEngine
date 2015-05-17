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
#include "Effect.h"
#include "Game.h"
#include "GameException.h"
#include "Utility.h"
#include "D3Dcompiler.h"

namespace Library
{
    Effect::Effect(Game& game)
        : mGame(game), mEffect(nullptr), mEffectDesc(), mTechniques(), mTechniquesByName(), mVariables(), mVariablesByName()
    {
    }

    Effect::~Effect()
    {
        for (Technique* technique : mTechniques)
        {
            delete technique;
        }
        mTechniques.clear();

        for (Variable* variable : mVariables)
        {
            delete variable;
        }
        mVariables.clear();

        ReleaseObject(mEffect);
    }

    void Effect::CompileEffectFromFile(ID3D11Device* direct3DDevice, ID3DX11Effect** effect, const std::wstring& filename)
    {
        UINT shaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
    shaderFlags |= D3DCOMPILE_DEBUG;
    shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

        ID3D10Blob* compiledShader = nullptr;
        ID3D10Blob* errorMessages = nullptr;
        HRESULT hr = D3DCompileFromFile(filename.c_str(), nullptr, nullptr, nullptr, "fx_5_0", shaderFlags, 0, &compiledShader, &errorMessages);
        if (errorMessages != nullptr)
        {
            GameException ex((char*)errorMessages->GetBufferPointer(), hr);
            ReleaseObject(errorMessages);

            throw ex;
        }

        if (FAILED(hr))
        {
            throw GameException("D3DX11CompileFromFile() failed.", hr);
        }

        hr = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), NULL, direct3DDevice, effect);
        if (FAILED(hr))
        {
            throw GameException("D3DX11CreateEffectFromMemory() failed.", hr);
        }

        ReleaseObject(compiledShader);
    }

    void Effect::LoadCompiledEffect(ID3D11Device* direct3DDevice, ID3DX11Effect** effect, const std::wstring& filename)
    {
        std::vector<char> compiledShader;
        Utility::LoadBinaryFile(filename, compiledShader);

        HRESULT hr = D3DX11CreateEffectFromMemory(&compiledShader.front(), compiledShader.size(), NULL, direct3DDevice, effect);
        if (FAILED(hr))
        {
            throw GameException("D3DX11CreateEffectFromMemory() failed.", hr);
        }
    }

    Game& Effect::GetGame()
    {
        return mGame;
    }

    ID3DX11Effect* Effect::GetEffect() const
    {
        return mEffect;
    }

    void Effect::SetEffect(ID3DX11Effect* effect)
    {
        if (mEffect != nullptr)
        {
            for (Technique* technique : mTechniques)
            {
                delete technique;
            }
            mTechniques.clear();

            for (Variable* variable : mVariables)
            {
                delete variable;
            }
            mVariables.clear();
        }

        mEffect = effect;
        Initialize();
    }

    const D3DX11_EFFECT_DESC& Effect::EffectDesc() const
    {
        return mEffectDesc;
    }

    const std::vector<Technique*>& Effect::Techniques() const	
    {
        return mTechniques;
    }

    const std::map<std::string, Technique*>& Effect::TechniquesByName() const
    {
        return mTechniquesByName;
    }

    const std::vector<Variable*>& Effect::Variables() const	
    {
        return mVariables;
    }

    const std::map<std::string, Variable*>& Effect::VariablesByName() const
    {
        return mVariablesByName;
    }

    void Effect::CompileFromFile(const std::wstring& filename)
    {
        CompileEffectFromFile(mGame.Direct3DDevice(), &mEffect, filename);
        Initialize();
    }

    void Effect::LoadCompiledEffect(const std::wstring& filename)
    {
        LoadCompiledEffect(mGame.Direct3DDevice(), &mEffect, filename);
        Initialize();
    }

    void Effect::Initialize()
    {
        HRESULT hr = mEffect->GetDesc(&mEffectDesc);
        if (FAILED(hr))
        {
            throw GameException("ID3DX11Effect::GetDesc() failed.", hr);
        }
        
        for (UINT i = 0; i < mEffectDesc.Techniques; i++)
        {
            Technique* technique = new Technique(mGame, *this, mEffect->GetTechniqueByIndex(i));
            mTechniques.push_back(technique);
            mTechniquesByName.insert(std::pair<std::string, Technique*>(technique->Name(), technique));
        }

        for (UINT i = 0; i < mEffectDesc.GlobalVariables; i++)
        {
            Variable* variable = new Variable(*this, mEffect->GetVariableByIndex(i));
            mVariables.push_back(variable);
            mVariablesByName.insert(std::pair<std::string, Variable*>(variable->Name(), variable));
        }
    }
}