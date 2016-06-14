//
//  GameMode.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/3/16.
//
//

#pragma once

#include "cocos2d.h"
#include "Enums.h"

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
        virtual ~GameMode() {}
        
        GameState getGameState() { return mGameState; }
        
        std::function<void(GameState)> onGameStateChanged;
        
        virtual void restartGame() = 0;
        
        virtual void setGameScene(MainGameScene* gameScene)
        {
            mGameScene = gameScene;
        }
        
        virtual int getTopScore() = 0;
        
        virtual GameModeType getGameModeType() = 0;
        
        virtual void handlePowerUp(PowerUpType type);
        
        virtual void pauseGame();
        virtual void resumeGame();
        bool isTimeStopped() { return mTimeStopped; }
        
        bool init();
        void update(float seconds);
        
    protected:
        virtual void setGameState(GameState newState);
        MainGameScene* getGameScene() { return mGameScene; }
        void setPowerUpMaxPerGame(PowerUpType type, int max) { mPowerUpMaxPerGame[type] = max; }
        
    private:
        GameState mGameState;
        MainGameScene* mGameScene;
        GameState mPausedState;
        std::map<PowerUpType, int> mPowerUpMaxPerGame;
        std::map<PowerUpType, int> mCurrentGamePowerUpUseCount;
        
        bool mTimeStopped;
        float mTimeStopRemaining;
    };
}
