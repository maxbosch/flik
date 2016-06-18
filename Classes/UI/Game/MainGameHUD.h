//
//  MainGameHUD.hpp
//  Fling
//
//  Created by Adam Eskreis on 6/1/16.
//
//

#pragma once

#include "GameHUD.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class DefaultGameOverOverlay;
    class MainGameScene;
    class MainGameHeader;
    class PauseOverlayWidget;
    class GameObjectiveOverlay;
    
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
        cocos2d::ui::Widget* mGameOverScreen;
        GameBoard* mGameBoard;
        MainGameHeader* mHeader;
        PauseOverlayWidget* mPauseOverlay;
        GameObjectiveOverlay* mObjectiveOverlay;
        
        virtual GameObjectiveOverlay* createObjectiveOverlay();
        virtual cocos2d::ui::Widget* createGameOverOverlay();
        virtual void onShowGameOverScreen();
    };
}