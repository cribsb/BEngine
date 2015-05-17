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
    class Keyboard : public GameComponent
    {
        RTTI_DECLARATIONS(Keyboard, GameComponent)

    public:
        Keyboard(Game& game, LPDIRECTINPUT8 directInput);
        ~Keyboard();

        const byte* const CurrentState() const;
        const byte* const LastState() const;

        virtual void Initialize() override;
        virtual void Update(const GameTime& gameTime) override;
        
        bool IsKeyUp(byte key) const;
        bool IsKeyDown(byte key) const;
		bool IsKeyUpC(std::string key) const;
		bool IsKeyDownC(std::string key) const;
        bool WasKeyUp(byte key) const;
        bool WasKeyDown(byte key) const;
        bool WasKeyPressedThisFrame(byte key) const;
        bool WasKeyReleasedThisFrame(byte key) const;
        bool IsKeyHeldDown(byte key) const;

    private:
        Keyboard();

        static const int KeyCount = 256;

        Keyboard(const Keyboard& rhs);

        LPDIRECTINPUT8 mDirectInput;
        LPDIRECTINPUTDEVICE8 mDevice;
        byte mCurrentState[KeyCount];
        byte mLastState[KeyCount];
    };
}