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
    class BonusBar;
    
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
        
        void showAchievements(const std::vector<std::string>& achievements) { mPendingAchievements = achievements; }
        
    protected:
        cocos2d::ui::Widget* mGameOverScreen;
        GameBoard* mGameBoard;
        MainGameHeader* mHeader;
        PauseOverlayWidget* mPauseOverlay;
        GameObjectiveOverlay* mObjectiveOverlay;
        cocos2d::ui::Layout* mTimerBar;
        BonusBar* mBonusBar;
        
        virtual GameObjectiveOverlay* createObjectiveOverlay();
        virtual cocos2d::ui::Widget* createGameOverOverlay();
        virtual void onShowGameOverScreen();
        void showObjectiveOverlay();
        
    private:
        std::vector<std::string> mPendingAchievements;
        
        void showAchievement(int index);
    };
}
