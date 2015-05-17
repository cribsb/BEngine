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
#include "Pass.h"

namespace Library
{
    class Game;
    class Effect;

    class Technique
    {
    public:
        Technique(Game& game, Effect& effect, ID3DX11EffectTechnique* technique);
        ~Technique();

        Effect& GetEffect();
        ID3DX11EffectTechnique* GetTechnique() const;
        const D3DX11_TECHNIQUE_DESC& TechniqueDesc() const;
        const std::string& Name() const;
        const std::vector<Pass*>& Passes() const;
        const std::map<std::string, Pass*>& PassesByName() const;

    private:
        Technique(const Technique& rhs);
        Technique& operator=(const Technique& rhs);

        Effect& mEffect;
        ID3DX11EffectTechnique* mTechnique;
        D3DX11_TECHNIQUE_DESC mTechniqueDesc;
        std::string mName;
        std::vector<Pass*> mPasses;
        std::map<std::string, Pass*> mPassesByName;
    };
}