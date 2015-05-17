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

#include <functional>
#include "DrawableGameComponent.h"

namespace Library
{
	class Effect;
    class Material;
	class Pass;
	
    class FullScreenQuad : public DrawableGameComponent
    {
        RTTI_DECLARATIONS(FullScreenQuad, DrawableGameComponent)

    public:
        FullScreenQuad(Game& game);
		FullScreenQuad(Game& game, Material& material);
        ~FullScreenQuad();

		Material* GetMaterial();
        void SetMaterial(Material& material, const std::string& techniqueName, const std::string& passName);
		void SetActiveTechnique(const std::string& techniqueName, const std::string& passName);
		void SetCustomUpdateMaterial(std::function<void()> callback);

        virtual void Initialize() override;
        virtual void Draw(const GameTime& gameTime) override;

    private:
        FullScreenQuad();
        FullScreenQuad(const FullScreenQuad& rhs);
        FullScreenQuad& operator=(const FullScreenQuad& rhs);

        Material* mMaterial;
        Pass* mPass;
		ID3D11InputLayout* mInputLayout;

		ID3D11Buffer* mVertexBuffer;
        ID3D11Buffer* mIndexBuffer;
		UINT mVertexCount;
		UINT mIndexCount;
		std::function<void()> mCustomUpdateMaterial;
    };
}