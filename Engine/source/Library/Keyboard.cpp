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
#include "Keyboard.h"
#include "Game.h"
#include "GameTime.h"
#include "GameException.h"

namespace Library
{
    RTTI_DEFINITIONS(Keyboard)

    Keyboard::Keyboard(Game& game, LPDIRECTINPUT8 directInput)
        : GameComponent(game), mDirectInput(directInput), mDevice(nullptr)
    {
        assert(mDirectInput != nullptr);		
        ZeroMemory(mCurrentState, sizeof(mCurrentState));
        ZeroMemory(mLastState, sizeof(mLastState));
    }

    Keyboard::~Keyboard()
    {
        if (mDevice != nullptr)
        {
            mDevice->Unacquire();
            mDevice->Release();
            mDevice = nullptr;
        }
    }

    const byte* const Keyboard::CurrentState() const
    {
        return mCurrentState;
    }

    const byte* const Keyboard::LastState() const
    {
        return mLastState;
    }

    void Keyboard::Initialize()
    {
        if (FAILED(mDirectInput->CreateDevice(GUID_SysKeyboard, &mDevice, nullptr)))
        {
            throw GameException("IDIRECTINPUT8::CreateDevice() failed");
        }

        if (FAILED(mDevice->SetDataFormat(&c_dfDIKeyboard)))
        {
            throw GameException("IDIRECTINPUTDEVICE8::SetDataFormat() failed");
        }

        if (FAILED(mDevice->SetCooperativeLevel(mGame->WindowHandle(), DISCL_FOREGROUND| DISCL_NONEXCLUSIVE)))
        {
            throw GameException("IDIRECTINPUTDEVICE8::SetCooperativeLevel() failed");
        }

		mDevice->Acquire();
    }

    void Keyboard::Update(const GameTime& gameTime)
    {
        if (mDevice != nullptr)
        {
            memcpy(mLastState, mCurrentState, sizeof(mCurrentState));

            if (FAILED(mDevice->GetDeviceState(sizeof(mCurrentState), (LPVOID)mCurrentState)))
            {
                // Try to reaqcuire the device
                if (SUCCEEDED(mDevice->Acquire()))
                {
                    mDevice->GetDeviceState(sizeof(mCurrentState), (LPVOID)mCurrentState);
                }				
            }
        }
    }

    bool Keyboard::IsKeyUp(byte key) const
    {
        return ((mCurrentState[key] & 0x80) == 0);
    }

    bool Keyboard::IsKeyDown(byte key) const
    {
        return ((mCurrentState[key] & 0x80) != 0);
    }

	Library::byte strToVK(std::string a)
	{
		if (a.length() == 1)
		{
			switch (a[0])
			{
			case 'a':
				return DIK_A;
			case 'b':
				return DIK_B;
			case 'c':
				return DIK_C;
			case 'd':
				return DIK_D;
			case 'e':
				return DIK_E;
			case 'f':
				return DIK_F;
			case 'g':
				return DIK_G;
			case 'h':
				return DIK_H;
			case 'i':
				return DIK_I;
			case 'j':
				return DIK_J;
			case 'k':
				return DIK_K;
			case 'l':
				return DIK_L;
			case 'm':
				return DIK_M;
			case 'n':
				return DIK_N;
			case 'o':
				return DIK_O;
			case 'p':
				return DIK_P;
			case 'q':
				return DIK_Q;
			case 'r':
				return DIK_R;
			case 's':
				return DIK_S;
			case 't':
				return DIK_T;
			case 'u':
				return DIK_U;
			case 'v':
				return DIK_V;
			case 'w':
				return DIK_W;
			case 'x':
				return DIK_X;
			case 'y':
				return DIK_Y;
			case 'z':
				return DIK_Z;
			case '1':
				return DIK_1;
			case '2':
				return DIK_2;
			case '3':
				return DIK_3;
			case '4':
				return DIK_4;
			case '5':
				return DIK_5;
			case '6':
				return DIK_6;
			case '7':
				return DIK_7;
			case '8':
				return DIK_8;
			case '9':
				return DIK_9;
			case '0':
				return DIK_0;
			}
		}

		if (a == "lshift")
		{
			return DIK_LSHIFT;
		}
		if (a == "rshift")
		{
			return DIK_RSHIFT;
		}
		if (a == "lctrl")
		{
			return DIK_LCONTROL;
		}
		if (a == "rctrl")
		{
			return DIK_RCONTROL;
		}
		if (a == "lalt")
		{
			return DIK_LALT;
		}
		if (a == "ralt")
		{
			return DIK_RALT;
		}
		if (a == "F1")
		{
			return DIK_F1;
		}
		if (a == "F2")
		{
			return DIK_F2;
		}
		if (a == "F3")
		{
			return DIK_F3;
		}
		if (a == "F4")
		{
			return DIK_F4;
		}
		if (a == "F5")
		{
			return DIK_F5;
		}
		if (a == "F6")
		{
			return DIK_F6;
		}
		if (a == "F7")
		{
			return DIK_F7;
		}
		if (a == "F8")
		{
			return DIK_F8;
		}
		if (a == "F9")
		{
			return DIK_F9;
		}
		if (a == "F10")
		{
			return DIK_F10;
		}
		if (a == "F11")
		{
			return DIK_F11;
		}
		if (a == "F12")
		{
			return DIK_F12;
		}
		if (a == "escape")
		{
			return DIK_ESCAPE;
		}
		if (a == "minus")
		{
			return DIK_MINUS;
		}
		if (a == "equals")
		{
			return DIK_EQUALS;
		}
		if (a == "back")
		{
			return DIK_BACK;
		}
		if (a == "tab")
		{
			return DIK_TAB;
		}
		if (a == "return" || a == "enter")
		{
			return DIK_RETURN;
		}
		if (a == "space")
		{
			return DIK_SPACE;
		}
		if (a == "numpad1")
		{
			return DIK_NUMPAD1;
		}
		if (a == "numpad2")
		{
			return DIK_NUMPAD2;
		}
		if (a == "numpad3")
		{
			return DIK_NUMPAD3;
		}
		if (a == "numpad4")
		{
			return DIK_NUMPAD4;
		}
		if (a == "numpad5")
		{
			return DIK_NUMPAD5;
		}
		if (a == "numpad6")
		{
			return DIK_NUMPAD6;
		}
		if (a == "numpad7")
		{
			return DIK_NUMPAD7;
		}
		if (a == "numpad8")
		{
			return DIK_NUMPAD8;
		}
		if (a == "numpad9")
		{
			return DIK_NUMPAD9;
		}
		if (a == "numpad0")
		{
			return DIK_NUMPAD0;
		}
		if (a == "decimal")
		{
			return DIK_DECIMAL;
		}
		if (a == "subtract")
		{
			return DIK_SUBTRACT;
		}
		if (a == "add")
		{
			return DIK_ADD;
		}
		if (a == "home")
		{
			return DIK_HOME;
		}
		if (a == "end")
		{
			return DIK_END;
		}
		if (a == "up")
		{
			return DIK_UP;
		}
		if (a == "down")
		{
			return DIK_DOWN;
		}
		if (a == "right")
		{
			return DIK_RIGHT;
		}
		if (a == "left")
		{
			return DIK_LEFT;
		}
		if (a == "pageup")
		{
			return DIK_PRIOR;
		}
		if (a == "pagedown")
		{
			return DIK_NEXT;
		}
		if (a == "insert")
		{
			return DIK_INSERT;
		}
		if (a == "delete")
		{
			return DIK_DELETE;
		}
		if (a == "numpadenter" || a == "numpadreturn")
		{
			return DIK_NUMPADENTER;
		}
	}

	/*Library::byte charToVK(char a)
	{
		switch (a)
		{
		case 'a':
			return DIK_A;
		case 'b':
			return DIK_B;
		case 'c':
			return DIK_C;
		case 'd':
			return DIK_D;
		case 'e':
			return DIK_E;
		case 'f':
			return DIK_F;
		case 'g':
			return DIK_G;
		case 'h':
			return DIK_H;
		case 'i':
			return DIK_I;
		case 'j':
			return DIK_J;
		case 'k':
			return DIK_K;
		case 'l':
			return DIK_L;
		case 'm':
			return DIK_M;
		case 'n':
			return DIK_N;
		case 'o':
			return DIK_O;
		case 'p':
			return DIK_P;
		case 'q':
			return DIK_Q;
		case 'r':
			return DIK_R;
		case 's':
			return DIK_S;
		case 't':
			return DIK_T;
		case 'u':
			return DIK_U;
		case 'v':
			return DIK_V;
		case 'w':
			return DIK_W;
		case 'x':
			return DIK_X;
		case 'y':
			return DIK_Y;
		case 'z':
			return DIK_Z;
		case '1':
			return DIK_1;
		case '2':
			return DIK_2;
		case '3':
			return DIK_3;
		case '4':
			return DIK_4;
		case '5':
			return DIK_5;
		case '6':
			return DIK_6;
		case '7':
			return DIK_7;
		case '8':
			return DIK_8;
		case '9':
			return DIK_9;
		case '0':
			return DIK_0;
		}
	}*/

	bool Keyboard::IsKeyUpC(std::string key) const
	{
		return ((mCurrentState[strToVK(key)] & 0x80) == 0);
	}

	bool Keyboard::IsKeyDownC(std::string key) const
	{
		return ((mCurrentState[strToVK(key)] & 0x80) != 0);
	}

    bool Keyboard::WasKeyUp(byte key) const
    {
        return ((mLastState[key] & 0x80) == 0);
    }

    bool Keyboard::WasKeyDown(byte key) const
    {
        return ((mLastState[key] & 0x80) != 0);
    }

    bool Keyboard::WasKeyPressedThisFrame(byte key) const
    {
        return (IsKeyDown(key) && WasKeyUp(key));
    }

    bool Keyboard::WasKeyReleasedThisFrame(byte key) const
    {
        return (IsKeyUp(key) && WasKeyDown(key));
    }

    bool Keyboard::IsKeyHeldDown(byte key) const
    {
        return (IsKeyDown(key) && WasKeyDown(key));
    }
}