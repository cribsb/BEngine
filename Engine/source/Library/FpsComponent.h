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

#include "DrawableGameComponent.h"

namespace DirectX
{
    class SpriteBatch;
    class SpriteFont;
}

namespace Library
{
    class FpsComponent : public DrawableGameComponent
    {
        RTTI_DECLARATIONS(FpsComponent, DrawableGameComponent)

    public:
        FpsComponent(Game& game);
        ~FpsComponent();

        XMFLOAT2& TextPosition();
        int FrameRate() const;

        virtual void Initialize() override;
        virtual void Update(const GameTime& gameTime) override;
        virtual void Draw(const GameTime& gameTime) override;

    private:
        FpsComponent();
        FpsComponent(const FpsComponent& rhs);
        FpsComponent& operator=(const FpsComponent& rhs);
        
        SpriteBatch* mSpriteBatch;
        SpriteFont* mSpriteFont;
        XMFLOAT2 mTextPosition;

        int mFrameCount;
        int mFrameRate;
        double mLastTotalElapsedTime;
    };
}