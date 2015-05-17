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

#include "Camera.h"

namespace Library
{
    class Keyboard;
    class Mouse;

    class FirstPersonCamera : public Camera
    {
        RTTI_DECLARATIONS(FirstPersonCamera, Camera)

    public:
        FirstPersonCamera(Game& game);
        FirstPersonCamera(Game& game, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);

        virtual ~FirstPersonCamera();

        const Keyboard& GetKeyboard() const;
        void SetKeyboard(Keyboard& keyboard);

        const Mouse& GetMouse() const;
        void SetMouse(Mouse& mouse);

        float& MouseSensitivity();
        float& RotationRate();
        float& MovementRate();		
        
        virtual void Initialize() override;
        virtual void Update(const GameTime& gameTime) override;

        static const float DefaultMouseSensitivity;
        static const float DefaultRotationRate;
        static const float DefaultMovementRate;        

    protected:
        float mMouseSensitivity;
        float mRotationRate;
        float mMovementRate;        

		Keyboard* mKeyboard;
        Mouse* mMouse;

    private:
        FirstPersonCamera(const FirstPersonCamera& rhs);
        FirstPersonCamera& operator=(const FirstPersonCamera& rhs);
    };
}

