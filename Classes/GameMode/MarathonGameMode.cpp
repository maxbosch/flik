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

USING_NS_CC;

namespace flik {
    static const std::string kSpawnTimerKey = "spawn-timer-key";
    
    static const int kDefaultSpawnCount = 4;
    static const float kDefaultSpawnInterval = 4.0f;
    static const float kMaxCoverage = 1.05;
    
    bool MarathonGameMode::init()
    {
        if (!GameMode::init())
        {
            return false;
        }
        
        auto pieceRemovedListener = EventListenerCustom::create(kPieceRemovedEvent, [](EventCustom* event) {
            Player::getMainPlayer()->addScore(1);
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(pieceRemovedListener, this);
        
        return true;
    }
    
    void MarathonGameMode::restartGame()
    {
        setGameState(GameState::Starting);
        
        mSpawnCount = kDefaultSpawnCount;
        mSpawnInterval = kDefaultSpawnInterval;
        mLastSpawnIteration = 0;
        mIterations = 0;
        
        getGameScene()->clearPieces();
        
        this->unschedule(kSpawnTimerKey);
        this->schedule([this](float time) {
            mIterations++;
            if (mIterations % 3 == 0) {
                mSpawnCount++;
            }
            
            /*if (mIterations - mLastSpawnIteration == mSpawnInterval) {
             
             mLastSpawnIteration = mIterations;
             }
             
             if (mIterations % 50 == 0) {
             mSpawnInterval = std::max(mSpawnInterval - 1, 1);
             }*/
            
            spawnPieces(mSpawnCount);
            
        }, mSpawnInterval, CC_REPEAT_FOREVER, 0.0f, kSpawnTimerKey);
        
        spawnPieces(mSpawnCount);
        
        Player::getMainPlayer()->resetScore();
        
        setGameState(GameState::InProgress);
        
    }
    
    void MarathonGameMode::spawnPieces(int count)
    {
        auto scene = getGameScene();
        auto gameBoardBounds = scene->getGameBoardBounds();
        
        for (int i = 0; i < count; i++) {
            auto boardArea = gameBoardBounds.size.width * gameBoardBounds.size.height;
            auto coverageArea = 0.0f;
            scene->enumeratePieces([&coverageArea](Node* piece) {
                auto bounds = piece->getBoundingBox();
                coverageArea += bounds.size.width * bounds.size.height;
            });
            
            if (coverageArea / boardArea >= kMaxCoverage) {
                // You lose
                setGameState(GameState::Finished);
                this->unschedule(kSpawnTimerKey);
            
                return;
            }
            
            auto spawnPosition = findOpenSpawnPosition();
            scene->spawnPiece(Util::getRandomPositionInRect(getGameScene()->getGameBoardBounds()));
        }
    }
    
    Vec2 MarathonGameMode::findOpenSpawnPosition()
    {
        auto contentSize = getGameScene()->getGameBoardBounds().size;
        return Vec2(contentSize.width * random(0.0, 1.0), contentSize.height * random(0.0, 1.0));
    }
    
    void MarathonGameMode::setGameState(GameState newState)
    {
        GameMode::setGameState(newState);
        
        if (newState == GameState::Finished) {
            Player::getMainPlayer()->recordScore("marathon");
        }
    }
    
    int MarathonGameMode::getTopScore()
    {
        return Player::getMainPlayer()->getTopScore("marathon");
    }
}
