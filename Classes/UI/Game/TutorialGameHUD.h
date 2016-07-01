//
//  TutorialGameHUD.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/29/16.
//
//

#pragma once

#include "cocos2d.h"
#include "GameHUD.h"
#include "Enums.h"

namespace flik
{
    class Animation;
    
    class TutorialGameHUD : public GameHUD
    {
    public:
        CREATE_FUNC(TutorialGameHUD);
        
        bool init();
        
        GameBoard* getGameBoard() { return mGameBoard; }
        
        void setArrowPosition(TutorialArrowPosition position, float rotation);
        
        void onGameStateChanged(GameState newState);
        
        void update(float t);
        
    private:
        GameBoard* mGameBoard;
        
        cocos2d::ui::ImageView* mArrow;
        cocos2d::ui::RelativeLayoutParameter* mArrowLayout;
        cocos2d::ui::Text* mTutorialText;
        
        std::shared_ptr<Animation> mTextAnimation;
        
        void executeTutorialIntroAnimation();
        void executeTutorialExitAnimation();
    };
}
