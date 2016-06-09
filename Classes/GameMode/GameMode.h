//
//  GameMode.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/3/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    enum class GameState
    {
        Starting,
        InProgress,
        Finished,
        Paused
    };
    
    class MainGameScene;
    
    class GameMode : public cocos2d::Node
    {
    public:
        GameState getGameState() { return mGameState; }
        
        std::function<void(GameState)> onGameStateChanged;
        
        virtual void restartGame() = 0;
        
        virtual void setGameScene(MainGameScene* gameScene)
        {
            mGameScene = gameScene;
        }
        
        virtual int getTopScore() = 0;
        
        virtual void pauseGame();
        virtual void resumeGame();
        
    protected:
        virtual void setGameState(GameState newState);
        MainGameScene* getGameScene() { return mGameScene; }
        
    private:
        GameState mGameState;
        MainGameScene* mGameScene;
        GameState mPausedState;
    };
}
