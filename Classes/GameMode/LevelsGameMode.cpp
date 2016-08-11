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
//#include "CCLuaEngine.h"
#include "Styles.h"
#include "GameBoard.h"
#include "MainGameScene.h"
#include "ReplaceSpawner.h"
#include "OneTimeSpawner.h"
#include "TimedSpawner.h"
#include "ObjectiveTracker.h"
#include "PiecesClearedObjectiveTracker.h"
#include "MaxOnBoardObjectiveTracker.h"
#include "Behavior.h"

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
        
        mLevelDesc = levelDesc;
        
        mProgress.setLevelDescription(levelDesc);
        
        return true;
    }
    
    void LevelsGameMode::restartGame()
    {
        GameMode::restartGame();
        
        for (auto objective : mObjectives) {
            objective->reset();
        }
    }
    
    void LevelsGameMode::update(float seconds)
    {
        GameMode::update(seconds);
        
        bool allCompleted = true;
        
        if (getGameState() == GameState::InProgress) {
            for (auto objective : mObjectives) {
                // If any objective is failed, it's game over
                if (!objective->finishWhenComplete()) {
                    if (objective->isFailed()) {
                        setGameState(GameState::Finished);
                        break;

                    }
                    
                    allCompleted = false;
                } else if (objective->finishWhenComplete()) {
                    allCompleted &= objective->isCompleted();
                }
            }
            
            if (allCompleted) {
                setGameState(GameState::Finished);
            }
        }
    }
    
    void LevelsGameMode::setGameScene(MainGameScene* scene)
    {
        GameMode::setGameScene(scene);
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        auto& sublevels = mLevelDesc->data["sublevels"];
        auto& level = sublevels[mLevelDesc->sublevelNum];
        
        if (level.HasMember("time_limit")) {
            setGameTime(level["time_limit"].GetInt());
        }
        
        if (level.HasMember("spawner")) {
            auto& spawner = level["spawner"];
            const std::string& type = spawner["type"].GetString();
            if (type == "replace") {
                int initialCount = spawner["initial_count"].GetInt();
                setSpawner(ReplaceSpawner::create(initialCount));
            } else if (type == "onetime") {
                int count = spawner["count"].GetInt();
                setSpawner(OneTimeSpawner::create(count));
            } else if (type == "timed") {
                int initialCount = spawner["initial_count"].GetInt();
                int count = spawner["count"].GetInt();
                float interval = spawner["interval"].GetDouble();
                setSpawner(TimedSpawner::create(initialCount, interval, count));
            }
        }
        
        auto& objectives = level["objectives"];
        if (objectives.IsArray() && objectives.Size() > 0) {
            auto& objective = objectives[0];
            std::string type = objective["type"].GetString();
            if (type == "clear") {
                int quantity = objective["quantity"].GetInt();
                auto objective = PiecesClearedObjectiveTracker::create(quantity);
                mObjectives.push_back(objective);
                addChild(objective);
            } else if (type == "max") {
                int quantity = objective["quantity"].GetInt();
                auto objective = MaxOnBoardObjectiveTracker::create(getGameScene(), quantity);
                mObjectives.push_back(objective);
                addChild(objective);
            }
        }
        
        if (level.HasMember("obstacles")) {
            auto& obstacles = level["obstacles"];
            for (int i = 0; i < obstacles.Size(); i++) {
                auto& obstacle = obstacles[i];
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
                                    collisionMask |= collision::GreenPiece;
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
    }
    
    int LevelsGameMode::getTopScore()
    {
        return 0;
    }
    
    GameModeType LevelsGameMode::getGameModeType()
    {
        return GameModeType::Levels;
    }
    
    bool LevelsGameMode::isObjectiveCompleted()
    {
        for (auto objective : mObjectives) {
            if (!objective->isCompleted()) {
                return false;
            }
        }
        
        return true;
    }
    
    void LevelsGameMode::setGameState(GameState state)
    {
        GameMode::setGameState(state);
        
        if (state == GameState::Finished) {
            if (isObjectiveCompleted()) {
                LevelInfo::getInstance()->completeLevel(mLevelDesc->levelNum);
            }
        }
    }
}