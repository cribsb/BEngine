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
#include "Technique.h"
#include "Variable.h"

namespace Library
{
    class Game;

    class Effect
    {
    public:
        Effect(Game& game);
        virtual ~Effect();

        static void CompileEffectFromFile(ID3D11Device* direct3DDevice, ID3DX11Effect** effect, const std::wstring& filename);
        static void LoadCompiledEffect(ID3D11Device* direct3DDevice, ID3DX11Effect** effect, const std::wstring& filename);

        Game& GetGame();
        ID3DX11Effect* GetEffect() const;
        void SetEffect(ID3DX11Effect* effect);
        const D3DX11_EFFECT_DESC& EffectDesc() const;
        const std::vector<Technique*>& Techniques() const;
        const std::map<std::string, Technique*>& TechniquesByName() const;
        const std::vector<Variable*>& Variables() const;
        const std::map<std::string, Variable*>& VariablesByName() const;

        void CompileFromFile(const std::wstring& filename);
        void LoadCompiledEffect(const std::wstring& filename);

    private:
        Effect(const Effect& rhs);
        Effect& operator=(const Effect& rhs);

        void Initialize();

        Game& mGame;
        ID3DX11Effect* mEffect;
        D3DX11_EFFECT_DESC mEffectDesc;
        std::vector<Technique*> mTechniques;
        std::map<std::string, Technique*> mTechniquesByName;
        std::vector<Variable*> mVariables;
        std::map<std::string, Variable*> mVariablesByName;
    };
}