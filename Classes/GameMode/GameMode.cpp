//
//  GameMode.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/3/16.
//
//

#include "GameMode.h"
#include "MainGameScene.h"
#include "Player.h"

namespace flik {
    bool GameMode::init()
    {
        if (!Node::init())
        {
            return false;
        }
        
        setPowerUpMaxPerGame(PowerUpType::Timestop, 1);
        setPowerUpMaxPerGame(PowerUpType::Target, 3);
        
        mCurrentGamePowerUpUseCount[PowerUpType::Timestop] = 0;
        mCurrentGamePowerUpUseCount[PowerUpType::Target] = 0;
        
        return true;
    }
    
    void GameMode::setGameState(GameState newState)
    {
        mGameState = newState;
        
        if (onGameStateChanged) {
            onGameStateChanged(newState);
        }
    }
    
    void GameMode::pauseGame()
    {
        mPausedState = mGameState;
        setGameState(GameState::Paused);
    }
    
    void GameMode::resumeGame()
    {
        setGameState(mPausedState);
    }
    
    void GameMode::restartGame()
    {
        setGameState(GameState::Starting);
        
        getGameScene()->clearPieces();
        
        Player::getMainPlayer()->resetScore();
        
        if (mSpawner) {
            mSpawner->start(getGameScene());
        }
        
        mTimeRemaining = mGameTime;
        
        scheduleUpdate();
        
        setGameState(GameState::InProgress);
    }
    
    void GameMode::handlePowerUp(PowerUpType type)
    {
        bool used = false;
        auto availableCount = Player::getMainPlayer()->getPowerUpCount(type);
        if (availableCount == 0) {
            // Bring user to store
        } else {
            if (mCurrentGamePowerUpUseCount[type] < mPowerUpMaxPerGame[type]) {
                mCurrentGamePowerUpUseCount[type] -= 1;
                
                switch (type) {
                    case PowerUpType::Timestop:
                        if (!mTimeStopped) {
                            mTimeStopped = true;
                            mTimeStopRemaining = 5;
                            used = true;
                        }
                        break;
                        
                    case PowerUpType::Target:
                        getGameScene()->clearPieces();
                        used = true;
                        break;
                }
            }
            
            if (used) {
                auto player = Player::getMainPlayer();
                player->consumePowerUp(type, 1);
            }
        }
    }
    
    void GameMode::update(float seconds)
    {
        Node::update(seconds);
        
        if (mTimeStopped) {
            mTimeStopRemaining -= seconds;
            
            if (mTimeStopRemaining <= 0) {
                mTimeStopRemaining = 0;
                mTimeStopped = false;
            }
        }
        
        if (mGameTime > 0) {
            if (getGameState() == GameState::InProgress && !isTimeStopped()) {
                mTimeRemaining -= seconds;
                
                if (mTimeRemaining <= 0) {
                    mTimeRemaining = 0;
                    setGameState(GameState::Finished);
                    
                    unscheduleUpdate();
                }
            }
        }
    }
}