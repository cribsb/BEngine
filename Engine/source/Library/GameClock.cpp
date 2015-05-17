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
#include "GameClock.h"
#include "GameTime.h"

namespace Library
{
    GameClock::GameClock()
        : mStartTime(), mCurrentTime(), mLastTime(), mFrequency()
    {
        mFrequency = GetFrequency();
        Reset();	
    }

    const LARGE_INTEGER& GameClock::StartTime() const
    {
        return mStartTime;
    }

    const LARGE_INTEGER& GameClock::CurrentTime() const
    {
        return mCurrentTime;
    }

    const LARGE_INTEGER& GameClock::LastTime() const
    {
        return mLastTime;
    }

    void GameClock::Reset()
    {
        GetTime(mStartTime);
        mCurrentTime = mStartTime;
        mLastTime = mCurrentTime;
    }

    double GameClock::GetFrequency() const
    {
        LARGE_INTEGER frequency;

        if (QueryPerformanceFrequency(&frequency) == false)
        {
            throw std::exception("QueryPerformanceFrequency() failed.");
        }

        return (double)frequency.QuadPart;
    }

    void GameClock::GetTime(LARGE_INTEGER& time) const
    {
        QueryPerformanceCounter(&time);
    }

    void GameClock::UpdateGameTime(GameTime& gameTime)
    {
        GetTime(mCurrentTime);
        gameTime.SetTotalGameTime((mCurrentTime.QuadPart - mStartTime.QuadPart) / mFrequency);
        gameTime.SetElapsedGameTime((mCurrentTime.QuadPart - mLastTime.QuadPart) / mFrequency);

        mLastTime = mCurrentTime;
    }
}