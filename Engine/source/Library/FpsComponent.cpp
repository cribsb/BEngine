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
#include "FpsComponent.h"
#include <sstream>
#include <iomanip>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include "Game.h"
#include "Utility.h"

namespace Library
{
    RTTI_DEFINITIONS(FpsComponent)

    FpsComponent::FpsComponent(Game& game)
        : DrawableGameComponent(game), mSpriteBatch(nullptr), mSpriteFont(nullptr), mTextPosition(0.0f, 20.0f),
          mFrameCount(0), mFrameRate(0), mLastTotalElapsedTime(0.0)
    {
    }
    
    FpsComponent::~FpsComponent()
    {
        DeleteObject(mSpriteFont);
        DeleteObject(mSpriteBatch);
    }

    XMFLOAT2& FpsComponent::TextPosition()
    {
        return mTextPosition;
    }

    int FpsComponent::FrameRate() const
    {
        return mFrameCount;
    }

    void FpsComponent::Initialize()
    {       
        SetCurrentDirectory(Utility::ExecutableDirectory().c_str());

        mSpriteBatch = new SpriteBatch(mGame->Direct3DDeviceContext());
        mSpriteFont = new SpriteFont(mGame->Direct3DDevice(), L"Content\\Fonts\\Arial_14_Regular.spritefont");
    }

    void FpsComponent::Update(const GameTime& gameTime)
    {
        if (gameTime.TotalGameTime() - mLastTotalElapsedTime >= 1)
        {
            mLastTotalElapsedTime = gameTime.TotalGameTime();
            mFrameRate = mFrameCount;
            mFrameCount = 0;
        }

        mFrameCount++;
    }

    void FpsComponent::Draw(const GameTime& gameTime)
    {
        mSpriteBatch->Begin();
            
        std::wostringstream fpsLabel;
        fpsLabel << std::setprecision(4) << L"Frame Rate: " << mFrameRate << "    Total Elapsed Time: " << gameTime.TotalGameTime();
        mSpriteFont->DrawString(mSpriteBatch, fpsLabel.str().c_str(), mTextPosition);

        mSpriteBatch->End();
    }
}