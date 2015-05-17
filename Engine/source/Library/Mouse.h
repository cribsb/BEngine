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
    class GameTime;

    enum MouseButtons
    {
        MouseButtonsLeft = 0,
        MouseButtonsRight = 1,
        MouseButtonsMiddle = 2,
        MouseButtonsX1 = 3
    };

    class Mouse : public GameComponent
    {
        RTTI_DECLARATIONS(Mouse, GameComponent)

    public:
        Mouse(Game& game, LPDIRECTINPUT8 directInput);
        ~Mouse();

        LPDIMOUSESTATE CurrentState();
        LPDIMOUSESTATE LastState();

        virtual void Initialize() override;
        virtual void Update(const GameTime& gameTime) override;
        
        long X() const;
        long Y() const;
        long Wheel() const;

        bool IsButtonUp(MouseButtons button) const;
        bool IsButtonDown(MouseButtons button) const;		
        bool WasButtonUp(MouseButtons button) const;
        bool WasButtonDown(MouseButtons button) const;	
        bool WasButtonPressedThisFrame(MouseButtons button) const;
        bool WasButtonReleasedThisFrame(MouseButtons button) const;
        bool IsButtonHeldDown(MouseButtons button) const;

    private:
        Mouse();

        LPDIRECTINPUT8 mDirectInput;
        LPDIRECTINPUTDEVICE8 mDevice;
        DIMOUSESTATE mCurrentState;
        DIMOUSESTATE mLastState;

        long mX;
        long mY;
        long mWheel;
    };
}