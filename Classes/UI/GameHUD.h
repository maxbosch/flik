//
//  GameHUD.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/3/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class MainGameScene;
    enum class GameState;
    
    class GameHUD : public cocos2d::ui::RelativeBox
    {
    public:
        virtual void onGameStateChanged(GameState newState) {}
        
        void setGameScene(MainGameScene* gameScene) { mGameScene = gameScene; }
        
    protected:
        MainGameScene* getGameScene() { return mGameScene; }
        
    private:
        MainGameScene* mGameScene;
    };
}
