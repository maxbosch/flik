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
#include "PieceSpawner.h"

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
        
        virtual void restartGame();
        
        virtual int getTopScore() = 0;
        
        int getPreviousTopScore() { return mPreviousTopScore; }
        
        virtual GameModeType getGameModeType() = 0;
        
        virtual void setGameScene(MainGameScene* gameScene)
        {
            mGameScene = gameScene;
        }
        
        virtual void handlePowerUp(PowerUpType type);
        
        virtual void pauseGame();
        virtual void resumeGame();
        bool isTimeStopped() { return mTimeStopped; }
        
        bool init();
        void update(float seconds);
        
        void setGameTime(float seconds) { mGameTime = seconds; }
        void addGameTime(float seconds) {
            mGameTime += seconds;
            mTimeRemaining += seconds;
        }
        float getTimeRemaining() { return mTimeRemaining; }
        float getGameTime() { return mGameTime; }
        
        void setSpawner(PieceSpawner* spawner);
        
        void addBonus(BonusType type);
        
        virtual void onBackPressed();
        
        const std::vector<BonusType>& getBonuses() { return mBonuses; }
        
        int getScoreMultiplier() { return mScoreMultiplier; }
        void setScoreMultiplier(int multiplier) { mScoreMultiplier = multiplier; }
        
        void setIgnoresTimestop(bool b) { mIgnoresTimestop = b; }
        
    protected:
        virtual void setGameState(GameState newState);
        MainGameScene* getGameScene() { return mGameScene; }
        void setPowerUpMaxPerGame(PowerUpType type, int max) { mPowerUpMaxPerGame[type] = max; }
        void stopTime(float seconds);
        
    private:
        GameState mGameState;
        MainGameScene* mGameScene;
        GameState mPausedState;
        std::map<PowerUpType, int> mPowerUpMaxPerGame;
        std::map<PowerUpType, int> mCurrentGamePowerUpUseCount;
        int mPreviousTopScore;
        
        bool mTimeStopped = false;
        float mTimeStopRemaining;
        bool mIgnoresTimestop = false;
        
        float mTimeRemaining = 0.0f;
        float mGameTime = 0.0f;
        std::vector<BonusType> mBonuses;
        
        PieceSpawner* mSpawner;
        
        int mScoreMultiplier = 1;
    };
}
