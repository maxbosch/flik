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
#include "GhostBonusBehavior.h"

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
                Player::getMainPlayer()->addScore(1 * getScoreMultiplier());
            }
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(pieceRemovedListener, this);
        
        setSpawner(IncreasingTimedSpawner::create(kDefaultSpawnCount, kDefaultSpawnInterval, kDefaultSpawnCount, 10.0f, 1));
        
        return true;
    }
    
    void MarathonGameMode::setGameState(GameState newState)
    {
        GameMode::setGameState(newState);
        
        if (newState == GameState::Finished) {
            auto player = Player::getMainPlayer();
            
            player->addCurrency(player->getCurrentScore());
            player->recordScore("marathon");
        }
    }
    
    int MarathonGameMode::getTopScore()
    {
        return Player::getMainPlayer()->getTopScore("marathon");
    }
    
    void MarathonGameMode::update(float seconds)
    {
        GameMode::update(seconds);
        
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
    
    void MarathonGameMode::setGameScene(MainGameScene* scene)
    {
        GameMode::setGameScene(scene);
        
        //addBonus(BonusType::Rainbow);
    }
}
