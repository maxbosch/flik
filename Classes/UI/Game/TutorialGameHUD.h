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
    class TutorialGameHUD : public GameHUD
    {
    public:
        CREATE_FUNC(TutorialGameHUD);
        
        bool init();
        
        GameBoard* getGameBoard() { return mGameBoard; }
        
        void setArrowPosition(TutorialArrowPosition position, float rotation);
        
        void onGameStateChanged(GameState newState);
        
    private:
        GameBoard* mGameBoard;
        
        cocos2d::ui::ImageView* mArrow;
        cocos2d::ui::RelativeLayoutParameter* mArrowLayout;
        cocos2d::ui::Text* mTutorialText;
        
        void executeTutorialIntroAnimation();
        void executeTutorialExitAnimation();
    };
}
