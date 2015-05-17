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
#include "Effect.h"

namespace Library
{
    class Model;
    class Mesh;

    class Material : public RTTI
    {
        RTTI_DECLARATIONS(Material, RTTI)		

    public:
        Material();
        Material(const std::string& defaultTechniqueName);
        virtual ~Material();

        Variable* operator[](const std::string& variableName);
        Effect* GetEffect() const;
        Technique* CurrentTechnique() const;
        void SetCurrentTechnique(Technique& currentTechnique);
        const std::map<Pass*, ID3D11InputLayout*>& InputLayouts() const;

        virtual void Initialize(Effect& effect);
        virtual void CreateVertexBuffer(ID3D11Device* device, const Model& model, std::vector<ID3D11Buffer*>& vertexBuffers) const;
        virtual void CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const = 0; 
        virtual UINT VertexSize() const = 0;

    protected:
        Material(const Material& rhs);
        Material& operator=(const Material& rhs);

        virtual void CreateInputLayout(const std::string& techniqueName, const std::string& passName, D3D11_INPUT_ELEMENT_DESC* inputElementDescriptions, UINT inputElementDescriptionCount);
		virtual void Material::CreateInputLayout(Pass& pass, D3D11_INPUT_ELEMENT_DESC* inputElementDescriptions, UINT inputElementDescriptionCount);

        Effect* mEffect;
        Technique* mCurrentTechnique;
        std::string mDefaultTechniqueName;
        std::map<Pass*, ID3D11InputLayout*> mInputLayouts;
    };

    #define MATERIAL_VARIABLE_DECLARATION(VariableName)	\
		public:											\
            Variable& VariableName() const;				\
		private:										\
            Variable* m ## VariableName;
        

    #define MATERIAL_VARIABLE_DEFINITION(Material, VariableName)	\
        Variable& Material::VariableName() const					\
        {															\
            return *m ## VariableName;								\
        }

    #define MATERIAL_VARIABLE_INITIALIZATION(VariableName) m ## VariableName(NULL)

    #define MATERIAL_VARIABLE_RETRIEVE(VariableName)						\
        m ## VariableName = mEffect->VariablesByName().at(#VariableName);
}