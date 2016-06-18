//
//  LevelGameMode.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/14/16.
//
//

#include "LevelsGameMode.h"
#include "Util.h"
#include "Events.h"
#include "GamePiece.h"
#include "Physics.h"

USING_NS_CC;

namespace flik
{
    LevelsGameMode* LevelsGameMode::create(const LevelDescription* levelDesc)
    {
        return createWithParams<LevelsGameMode>(levelDesc);
    }
    
    bool LevelsGameMode::init(const LevelDescription* levelDesc)
    {
        if (!TimedGameMode::init())
        {
            return false;
        }
        
        setGameTime(levelDesc->timeLimit);
        
        mLevelDesc = levelDesc;
        
        mProgress.setLevelDescription(levelDesc);
        
        auto pieceRemovedListener = EventListenerCustom::create(kPieceRemovedEvent, [this](EventCustom* event) {
            auto piece = reinterpret_cast<GamePiece*>(event->getUserData());
            
            ObjectiveIncrementUpdate update;
            switch (piece->getType()) {
                case collision::RedPiece:
                    update.type = ObjectiveType::CollectRedPiece;
                    break;
                    
                case collision::BluePiece:
                    update.type = ObjectiveType::CollectBluePiece;
                    break;
                    
                case collision::YellowPiece:
                    update.type = ObjectiveType::CollectYellowPiece;
                    break;
                    
                case collision::PinkPiece:
                    update.type = ObjectiveType::CollectPinkPiece;
                    break;
                    
                default:
                    break;
            }
            
            update.increment = 1;
            
            mProgress.incrementObjective(update.type, update.increment);
            
            if (mProgress.isCompleted()) {
                LevelInfo::getInstance()->completeLevel(mLevelDesc->levelNum);
                setGameState(GameState::Finished);
            }
            
            EventCustom eventObj(kObjectiveUpdatedEvent);
            eventObj.setUserData(&update);
            
            getEventDispatcher()->dispatchEvent(&eventObj);
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(pieceRemovedListener, this);
        
        return true;
    }
    
    void LevelsGameMode::restartGame()
    {
        TimedGameMode::restartGame();
        
        mProgress.reset();
    }
    
    int LevelsGameMode::getTopScore()
    {
        return 0;
    }
    
    GameModeType LevelsGameMode::getGameModeType()
    {
        return GameModeType::Levels;
    }
}