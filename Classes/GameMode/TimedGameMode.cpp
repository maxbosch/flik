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
#include "ReplaceSpawner.h"


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
            if (getGameState() == GameState::InProgress) {
                Player::getMainPlayer()->addScore(1 * getScoreMultiplier());
            }
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(pieceRemovedListener, this);
        
        setSpawner(ReplaceSpawner::create(kInitialSpawnCount));
        
        return true;
    }
    
    void TimedGameMode::setGameState(GameState newState)
    {
        GameMode::setGameState(newState);
        
        if (newState == GameState::Finished) {
            auto player = Player::getMainPlayer();
            player->addCurrency(player->getCurrentScore());
            player->recordScore("timed");
        }
    }
    
    int TimedGameMode::getTopScore()
    {
        return Player::getMainPlayer()->getTopScore("timed");
    }
}
