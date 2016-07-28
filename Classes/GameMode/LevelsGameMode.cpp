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
#include "CCLuaEngine.h"
#include "Styles.h"
#include "GameBoard.h"
#include "MainGameScene.h"
#include "ReplaceSpawner.h"

USING_NS_CC;

namespace flik
{
    LevelsGameMode* LevelsGameMode::create(const LevelDescription* levelDesc)
    {
        return createWithParams<LevelsGameMode>(levelDesc);
    }
    
    bool LevelsGameMode::init(const LevelDescription* levelDesc)
    {
        if (!GameMode::init())
        {
            return false;
        }
        
        setGameTime(levelDesc->timeLimit);
        
        mLevelDesc = levelDesc;
        
        mProgress.setLevelDescription(levelDesc);
        
        auto pieceRemovedListener = EventListenerCustom::create(kPieceRemovedEvent, [this](EventCustom* event) {
            ObjectiveIncrementUpdate update;
            update.type = ObjectiveType::CollectPiece;
            
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
        auto uiSize = Director::getInstance()->getVisibleSize();
        
        if (mLevelDesc->timeLimit > 0) {
            setGameTime(mLevelDesc->timeLimit);
        }
        
        setSpawner(ReplaceSpawner::create(5));
        
        if (mLevelDesc->obstacles.IsArray()) {
            for (int i = 0; i < mLevelDesc->obstacles.Size(); i++) {
                auto& obstacle = mLevelDesc->obstacles[i];
                if (obstacle.IsObject()) {
                    std::string type = obstacle["type"].GetString();
                    if (type == "wall") {
                        int collisionMask = collision::AllPieces;
                        int categoryMask = collision::BlackRail;
                        auto& colors = obstacle["colors"];
                        if (colors.IsArray() && colors.Size() > 0) {
                            collisionMask = 0;
                            for (int i = 0; i < colors.Size(); i++) {
                                std::string color = colors[i].GetString();
                                if (color == "red") {
                                    collisionMask |= collision::RedPiece;
                                } else if (color == "blue") {
                                    collisionMask |= collision::BluePiece;
                                } else if (color == "green") {
                                    collisionMask |= collision::PinkPiece;
                                } else if (color == "yellow") {
                                    collisionMask |= collision::YellowPiece;
                                }
                            }
                        }
                        
                        auto parsePoint = [&](const rapidjson::Value& pointValue) -> Vec2 {
                            auto x = (pointValue["x"].GetDouble() / 100.0) * uiSize.width;
                            auto y = (pointValue["y"].GetDouble() / 100.0) * uiSize.height;
                            
                            return Vec2(x, y);
                        };
                        
                        auto parseSize = [&](const rapidjson::Value& pointValue) -> Size {
                            auto x = (pointValue["width"].GetDouble() / 100.0) * uiSize.width;
                            auto y = (pointValue["height"].GetDouble() / 100.0) * uiSize.height;
                            
                            return Size(x, y);
                        };
                        
                        auto position = parsePoint(obstacle["position"]);
                        auto size = parseSize(obstacle["size"]);
                        auto rotation = obstacle["rotation"].GetDouble();
                        
                        auto layer = LayerColor::create(Color4B(Color3B::WHITE));
                        layer->setContentSize(size);
                        layer->setPosition(position);
                        layer->setAnchorPoint(Vec2(0, 0));
                        layer->setRotation(rotation);
                        layer->ignoreAnchorPointForPosition(false);
                        
                        auto physicsBody = PhysicsBody::createBox(layer->getContentSize(), PhysicsMaterial(1.0f, 0.5f, 0.0f));
                        physicsBody->setRotationOffset(layer->getRotation());
                        physicsBody->setDynamic(false);
                        physicsBody->setCategoryBitmask(collision::BlackRail);
                        physicsBody->setContactTestBitmask(collision::All);
                        physicsBody->setCollisionBitmask(collision::All);
                        physicsBody->setRotationEnable(true);
                        layer->setPhysicsBody(physicsBody);
                        
                        getGameScene()->getGameBoard()->addChild(layer);
                        
                    }
                }
            }
        }
        
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