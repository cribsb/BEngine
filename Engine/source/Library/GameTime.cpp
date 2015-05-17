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
#include "GameTime.h"

namespace Library
{
	GameTime::GameTime()
		: mTotalGameTime(0.0), mElapsedGameTime(0.0)
	{
	}

	GameTime::GameTime(double totalGameTime, double elapsedGameTime)
		: mTotalGameTime(totalGameTime), mElapsedGameTime(elapsedGameTime)
	{
	}

	double GameTime::TotalGameTime() const
	{
		return mTotalGameTime;
	}

	void GameTime::SetTotalGameTime(double totalGameTime)
	{
		mTotalGameTime = totalGameTime;
	}

	double GameTime::ElapsedGameTime() const
	{
		return mElapsedGameTime;
	}

	void GameTime::SetElapsedGameTime(double elapsedGameTime)
	{
		mElapsedGameTime = elapsedGameTime;
	}
}