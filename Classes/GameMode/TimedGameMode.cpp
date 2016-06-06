//
//  TimedGameMode.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/6/16.
//
//

#include "TimedGameMode.h"
#include "Events.h"
#include "Player.h"
#include "MainGameScene.h"
#include "Util.h"

USING_NS_CC;

namespace flik
{
    static const int kInitialSpawnCount = 5;
    
    TimedGameMode* TimedGameMode::createWithTime(float seconds)
    {
        auto obj = TimedGameMode::create();
        obj->setGameTime(seconds);
        return obj;
    }
    
    bool TimedGameMode::init()
    {
        if (!GameMode::init())
        {
            return false;
        }
        
        auto pieceRemovedListener = EventListenerCustom::create(kPieceRemovedEvent, [this](EventCustom* event) {
            Player::getMainPlayer()->addScore(1);

            getGameScene()->spawnPiece(Util::getRandomPositionInRect(getGameScene()->getGameBoardBounds()));
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(pieceRemovedListener, this);
        
        return true;
    }
    
    
    void TimedGameMode::restartGame()
    {
        setGameState(GameState::Starting);
        
        getGameScene()->clearPieces();
        
        Player::getMainPlayer()->resetScore();
        
        mTimeRemaining = mGameTime + 0.99;
        
        for (int i = 0; i < kInitialSpawnCount; i++) {
            getGameScene()->spawnPiece(Util::getRandomPositionInRect(getGameScene()->getGameBoardBounds()));
        }
        
        scheduleUpdate();
        
        setGameState(GameState::InProgress);
    }
    
    void TimedGameMode::update(float seconds)
    {
        GameMode::update(seconds);
        
        mTimeRemaining -= seconds;
        
        if (floor(mTimeRemaining) <= 0) {
            mTimeRemaining = 0;
            setGameState(GameState::Finished);
            
            unscheduleUpdate();
        }
    }
    
    void TimedGameMode::setGameState(GameState newState)
    {
        GameMode::setGameState(newState);
        
        if (newState == GameState::Finished) {
            Player::getMainPlayer()->recordScore("timed");
        }
    }
    
    int TimedGameMode::getTopScore()
    {
        return Player::getMainPlayer()->getTopScore("timed");
    }
}
