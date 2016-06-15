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
        
        virtual bool init();
        
        virtual void setContentSize(const cocos2d::Size& size);
        
        void onGameStateChanged(GameState newState);
        
        void update(float time);
        
        GameBoard* getGameBoard();
        
    protected:
        GameOverWidget* mGameOverScreen;
        GameBoard* mGameBoard;
        MainGameHeader* mHeader;
        PauseOverlayWidget* mPauseOverlay;
    };
}