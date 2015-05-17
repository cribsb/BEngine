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

#include <windows.h>
#include <exception>

namespace Library
{
    class GameTime;

    class GameClock
    {
    public:
        GameClock();

        const LARGE_INTEGER& StartTime() const;
        const LARGE_INTEGER& CurrentTime() const;
        const LARGE_INTEGER& LastTime() const;

        void Reset();
        double GetFrequency() const;
        void GetTime(LARGE_INTEGER& time) const;
        void UpdateGameTime(GameTime& gameTime);

    private:
        GameClock(const GameClock& rhs);
        GameClock& operator=(const GameClock& rhs);

        LARGE_INTEGER mStartTime;
        LARGE_INTEGER mCurrentTime;
        LARGE_INTEGER mLastTime;
        double mFrequency;
    };
}
