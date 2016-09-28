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
#include "GhostBonusBehavior.h"
#include "RainbowBonusBehavior.h"
#include "ScoreMultiplierBonusBehavior.h"
#include "GravityBonusBehavior.h"
#include "SceneManager.h"
#include "Styles.h"
#include "GameBoard.h"
#include "Events.h"
#include "GamePiece.h"
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
        
        if (newState == GameState::Finished) {
            if (mSpawner) {
                mSpawner->stop(getGameScene());
            }
        }
        
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
        
        mBonuses.push_back(BonusType::AddTime);
        mBonuses.push_back(BonusType::Ghost);
        mBonuses.push_back(BonusType::Rainbow);
        
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
        /*auto availableCount = Player::getMainPlayer()->getPowerUpCount(type);
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
        }*/
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
            
            if (mGameState == GameState::InProgress) {
                auto visibleBounds = Rect(Vec2(), Director::getInstance()->getOpenGLView()->getDesignResolutionSize());
                
                auto gameBoard = getGameScene()->getGameBoard();
                auto localBounds = Rect(Vec2(0, 0), gameBoard->getContentSize());
                auto pieces = getGameScene()->getGameBoard()->getPieces();
                for (auto piece : pieces) {
                    bool outsideBounds = !localBounds.intersectsRect(piece->getBoundingBox());
                    if (outsideBounds) {
                        EventCustom eventObj(kPieceRemovedEvent);
                        eventObj.setUserData(piece);
                        
                        getEventDispatcher()->dispatchEvent(&eventObj);
                        
                        piece->removeFromParent();
                    }
                }
            }
        }
    }
    
    void GameMode::setSpawner(PieceSpawner* spawner)
    {
        if (mSpawner) {
            mSpawner->removeFromParent();
            mSpawner = nullptr;
        }
        
        mSpawner = std::move(spawner);
        addChild(spawner);
    }
    
    void GameMode::addBonus(BonusType type)
    {
        switch (type)
        {
            case BonusType::Rainbow:
                addChild(RainbowBonusBehavior::create(getGameScene(), 10));
                break;
                
            case BonusType::AddTime:
                addGameTime(5);
                break;
                
            case BonusType::Ghost:
                addChild(GhostBonusBehavior::create(getGameScene(), 10));
                break;
                
            case BonusType::DoubleUp:
                addChild(ScoreMultiplierBonusBehavior::create(getGameScene(), 10, 2));
                break;
                
            case BonusType::Gravity:
                addChild(GravityBonusBehavior::create(getGameScene(), 10));
                break;
                
            default:
                break;
        }
    }
    
    void GameMode::onBackPressed()
    {
        if (getGameState() == GameState::Paused) {
            resumeGame();
        } else if (getGameState() == GameState::InProgress) {
            pauseGame();
        } else {
            SceneManager::popSceneWithTransition<TransitionSlideInL>(kTransitionDuration);
        }
    }
}
