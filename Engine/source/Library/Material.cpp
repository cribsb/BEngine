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
#include "Material.h"
#include "GameException.h"
#include "Model.h"

namespace Library
{	
    RTTI_DEFINITIONS(Material)

    Material::Material()
        : mEffect(nullptr), mCurrentTechnique(nullptr), mDefaultTechniqueName(), mInputLayouts()
    {
    }

    Material::Material(const std::string& defaultTechniqueName)
        : mEffect(nullptr), mCurrentTechnique(nullptr), mDefaultTechniqueName(defaultTechniqueName), mInputLayouts()
    {
    }

    Material::~Material()
    {
        for (std::pair<Pass*, ID3D11InputLayout*> inputLayout : mInputLayouts)
        {
            ReleaseObject(inputLayout.second);
        }
    }

    Variable* Material::operator[](const std::string& variableName)
    {
        const std::map<std::string, Variable*>& variables = mEffect->VariablesByName();
        Variable* foundVariable = nullptr;		

        std::map<std::string, Variable*>::const_iterator found = variables.find(variableName);
        if (found != variables.end())
        {
            foundVariable = found->second;
        }

        return foundVariable;
    }

    Effect* Material::GetEffect() const
    {
        return mEffect;
    }

    Technique* Material::CurrentTechnique() const
    {
        return mCurrentTechnique;
    }
    
    void Material::SetCurrentTechnique(Technique& currentTechnique)
    {
        mCurrentTechnique = &currentTechnique;
    }

    const std::map<Pass*, ID3D11InputLayout*>& Material::InputLayouts() const
    {
        return mInputLayouts;
    }

    void Material::Initialize(Effect& effect)
    {
		for (std::pair<Pass*, ID3D11InputLayout*> inputLayout : mInputLayouts)
        {
            ReleaseObject(inputLayout.second);
        }
		mInputLayouts.clear();

        mEffect = &effect;

        Technique* defaultTechnique = nullptr;
        assert(mEffect->Techniques().size() > 0);
        if (mDefaultTechniqueName.empty() == false)
        {
            defaultTechnique = mEffect->TechniquesByName().at(mDefaultTechniqueName);
            assert(defaultTechnique != nullptr);
        }
        else
        {
            defaultTechnique = mEffect->Techniques().at(0);
        }

        SetCurrentTechnique(*defaultTechnique);
    }
    
    void Material::CreateVertexBuffer(ID3D11Device* device, const Model& model, std::vector<ID3D11Buffer*>& vertexBuffers) const
    {
        vertexBuffers.reserve(model.Meshes().size());
        for (Mesh* mesh : model.Meshes())
        {
            ID3D11Buffer* vertexBuffer;
            CreateVertexBuffer(device, *mesh, &vertexBuffer);
            vertexBuffers.push_back(vertexBuffer);
        }
    }

    void Material::CreateInputLayout(const std::string& techniqueName, const std::string& passName, D3D11_INPUT_ELEMENT_DESC* inputElementDescriptions, UINT inputElementDescriptionCount)
    {
        Technique* technique = mEffect->TechniquesByName().at(techniqueName);
        assert(technique != nullptr);

        Pass* pass = technique->PassesByName().at(passName);
        assert(pass != nullptr);

        ID3D11InputLayout* inputLayout;
        pass->CreateInputLayout(inputElementDescriptions, inputElementDescriptionCount, &inputLayout);

        mInputLayouts.insert(std::pair<Pass*, ID3D11InputLayout*>(pass, inputLayout));
    }

	void Material::CreateInputLayout(Pass& pass, D3D11_INPUT_ELEMENT_DESC* inputElementDescriptions, UINT inputElementDescriptionCount)
    {
        ID3D11InputLayout* inputLayout;
        pass.CreateInputLayout(inputElementDescriptions, inputElementDescriptionCount, &inputLayout);

        mInputLayouts.insert(std::pair<Pass*, ID3D11InputLayout*>(&pass, inputLayout));
    }
}