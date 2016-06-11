//
//  MainGameHUD.hpp
//  Fling
//
//  Created by Adam Eskreis on 6/1/16.
//
//

#pragma once

#include "GameHUD.h"

namespace flik
{
    class GameOverWidget;
    class MainGameScene;
    class MainGameHeader;
    class PauseOverlayWidget;
    
    class MainGameHUD : public GameHUD
    {
    public:
        virtual ~MainGameHUD();
        
        CREATE_FUNC(MainGameHUD);
        
        bool init();
        
        virtual void setContentSize(const cocos2d::Size& size);
        
        void onGameStateChanged(GameState newState);
        
        void update(float time);
        
        cocos2d::Node* getGameBoard();
        
    private:
        cocos2d::ui::Text* mScoreValueLabel;
        cocos2d::ui::Text* mTopScoreValueLabel;
        GameOverWidget* mGameOverScreen;
        cocos2d::Node* mGameBoard;
        MainGameHeader* mHeader;
        PauseOverlayWidget* mPauseOverlay;
    };
}