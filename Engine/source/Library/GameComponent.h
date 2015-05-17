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

#include "Common.h"

namespace Library
{
    class Game;
    class GameTime;

    class GameComponent : public RTTI
    {
        RTTI_DECLARATIONS(GameComponent, RTTI)

    public:
        GameComponent();
        GameComponent(Game& game);
        virtual ~GameComponent();

        Game* GetGame();
        void SetGame(Game& game);
        bool Enabled() const;
        void SetEnabled(bool enabled);

        virtual void Initialize();
		virtual void Update(const GameTime& gameTime);

    protected:
        Game* mGame;
        bool mEnabled;

    private:
        GameComponent(const GameComponent& rhs);
        GameComponent& operator=(const GameComponent& rhs);

    };
}
