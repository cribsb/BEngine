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
#include "Technique.h"
#include "Game.h"

namespace Library
{
    Technique::Technique(Game& game, Effect& effect, ID3DX11EffectTechnique* technique)
        : mEffect(effect), mTechnique(technique), mTechniqueDesc(), mName(), mPasses(), mPassesByName()
    {
        mTechnique->GetDesc(&mTechniqueDesc);
        mName = mTechniqueDesc.Name;

        for (UINT i = 0; i < mTechniqueDesc.Passes; i++)
        {
            Pass* pass = new Pass(game, *this, mTechnique->GetPassByIndex(i));
            mPasses.push_back(pass);
            mPassesByName.insert(std::pair<std::string, Pass*>(pass->Name(), pass));
        }
    }

    Technique::~Technique()
    {
        for (Pass* pass : mPasses)
        {
            delete pass;
        }
    }

    Effect& Technique::GetEffect()
    {
        return mEffect;
    }

    ID3DX11EffectTechnique* Technique::GetTechnique() const
    {
        return mTechnique;
    }

    const D3DX11_TECHNIQUE_DESC& Technique::TechniqueDesc() const
    {
        return mTechniqueDesc;
    }

    const std::string& Technique::Name() const
    {
        return mName;
    }

    const std::vector<Pass*>& Technique::Passes() const
    {
        return mPasses;
    }

    const std::map<std::string, Pass*>& Technique::PassesByName() const
    {
        return mPassesByName;
    }
}