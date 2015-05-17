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
#include "GameComponent.h"
#include "GameTime.h"

namespace Library
{
    RTTI_DEFINITIONS(GameComponent)

    GameComponent::GameComponent()
        : mGame(nullptr), mEnabled(true)
    {
    }

    GameComponent::GameComponent(Game& game)
        : mGame(&game), mEnabled(true)
    {
    }

    GameComponent::~GameComponent()
    {
    }

    Game* GameComponent::GetGame()
    {
        return mGame;
    }

    void GameComponent::SetGame(Game& game)
    {
        mGame = &game;
    }

    bool GameComponent::Enabled() const
    {
        return mEnabled;
    }

    void GameComponent::SetEnabled(bool enabled)
    {
        mEnabled = enabled;
    }

    void GameComponent::Initialize()
	{
	}

    void GameComponent::Update(const GameTime& gameTime)
    {
    }
}
