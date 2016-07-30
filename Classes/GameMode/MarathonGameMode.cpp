//
//  MarathonGameMode.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/3/16.
//
//

#include "MarathonGameMode.h"
#include "MainGameScene.h"
#include "Events.h"
#include "Player.h"
#include "Util.h"
#include "IncreasingTimedSpawner.h"

USING_NS_CC;

namespace flik {
    static const int kDefaultSpawnCount = 4;
    static const float kDefaultSpawnInterval = 4.0f;
   
    bool MarathonGameMode::init()
    {
        if (!GameMode::init())
        {
            return false;
        }
        
        auto pieceRemovedListener = EventListenerCustom::create(kPieceRemovedEvent, [this](EventCustom* event) {
            if (getGameState() == GameState::InProgress) {
                Player::getMainPlayer()->addScore(1);
            }
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(pieceRemovedListener, this);
        
        setSpawner(IncreasingTimedSpawner::create(kDefaultSpawnCount, kDefaultSpawnInterval, 10.0f, 1, kDefaultSpawnCount));
        
        return true;
    }
    
    void MarathonGameMode::setGameState(GameState newState)
    {
        if (newState == GameState::Finished) {
            Player::getMainPlayer()->recordScore("marathon");
        }
        
        GameMode::setGameState(newState);
    }
    
    int MarathonGameMode::getTopScore()
    {
        return Player::getMainPlayer()->getTopScore("marathon");
    }
    
    void MarathonGameMode::update(float seconds)
    {
        if (getGameScene()->getPiecesCount() > 70) {
            // You lose
            setGameState(GameState::Finished);
            return;
        }

    }
    
    void MarathonGameMode::handlePowerUp(PowerUpType type)
    {
        switch (type) {
            case PowerUpType::Timestop:
                
                break;
                
            default:
                break;
        }
    }
}
