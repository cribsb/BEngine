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

#include "GameComponent.h"

namespace Library
{
    class Camera;

    class DrawableGameComponent : public GameComponent
    {
        RTTI_DECLARATIONS(DrawableGameComponent, GameComponent)

    public:
        DrawableGameComponent();
        DrawableGameComponent(Game& game);
        DrawableGameComponent(Game& game, Camera& camera);
        virtual ~DrawableGameComponent();

        bool Visible() const;
        void SetVisible(bool visible);

        Camera* GetCamera();
        void SetCamera(Camera* camera);

        virtual void Draw(const GameTime& gameTime);

    protected:
        bool mVisible;
        Camera* mCamera;

    private:
        DrawableGameComponent(const DrawableGameComponent& rhs);
        DrawableGameComponent& operator=(const DrawableGameComponent& rhs);
    };
}