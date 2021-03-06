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
#include "Player.h"
#include "PhysicsNode.h"
#include "SceneManager.h"

USING_NS_CC;

namespace flik
{
    LevelsGameMode* LevelsGameMode::create(const LevelDescription* levelDesc, int sublevel)
    {
        return createWithParams<LevelsGameMode>(levelDesc, sublevel);
    }
    
    bool LevelsGameMode::init(const LevelDescription* levelDesc, int sublevel)
    {
        if (!GameMode::init())
        {
            return false;
        }
        
        mLevelDesc = levelDesc;
        mSublevel = sublevel;
        
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
        auto& level = sublevels[mSublevel];
        
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
                setSpawner(TimedSpawner::create(initialCount, interval, count, false));
            }
        }
        
        auto& objectives = level["objectives"];
        if (objectives.IsArray() && objectives.Size() > 0) {
            auto& objective = objectives[0];
            std::string type = objective["type"].GetString();
            if (type == "clear") {
                int quantity = objective["quantity"].GetInt();
                auto objective = PiecesClearedObjectiveTracker::create(getGameScene(), quantity);
                mObjectives.push_back(objective);
                addChild(objective);
            } else if (type == "max") {
                int quantity = objective["quantity"].GetInt();
                auto objective = MaxOnBoardObjectiveTracker::create(getGameScene(), quantity);
                mObjectives.push_back(objective);
                addChild(objective);
                setIgnoresTimestop(true);
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
                        layer->setAnchorPoint(Vec2(0.5, 0.5));
                        layer->setRotation(rotation);
                        layer->ignoreAnchorPointForPosition(false);
                        getGameScene()->getGameBoard()->addChild(layer);
                        
//                        auto physicsBody = PhysicsBody::createBox(layer->getContentSize(), PhysicsMaterial(1.0f, 0.5f, 0.0f));
//                        physicsBody->setRotationOffset(layer->getRotation());
//                        physicsBody->setDynamic(false);
//                        physicsBody->setCategoryBitmask(collision::BlackRail);
//                        physicsBody->setContactTestBitmask(collision::All);
//                        physicsBody->setCollisionBitmask(collision::All);
//                        physicsBody->setRotationEnable(true);
//                        layer->setPhysicsBody(physicsBody);
                        
                        auto physicsNode = PhysicsNode::create();
                        physicsNode->setContentSize(size);
                        physicsNode->setPosition(position);
                        physicsNode->setAnchorPoint(Vec2(0.5, 0.5));
                        physicsNode->setRotation(rotation);
                        physicsNode->setImpenetrable(true);
                        
                        b2BodyDef bodyDef;
                        bodyDef.type = b2_staticBody;
                        physicsNode->createPhysicsBody(getGameScene()->getPhysicsWorldBox2D(), &bodyDef);
                        physicsNode->addBoxFixture(size, 1.0, 0.0, 0.5, collision::BlackRail, collision::All);
                        getGameScene()->getGameBoard()->addChild(physicsNode);
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
        if (state == GameState::Finished) {
            if (isObjectiveCompleted()) {
                int score = 1;
                std::string name = mLevelDesc->data["name"].GetString();
                auto& sublevel = mLevelDesc->data["sublevels"][mSublevel];
                
                if (name == "intro" || name == "walls" || name == "clear") {
                    
                    int timeLimit = sublevel["time_limit"].GetInt();
                    float remainingPercentage = (float)getTimeRemaining() / (float)timeLimit;
                    if (remainingPercentage > 0.4) {
                        score = 3;
                    } else if (remainingPercentage > 0.2) {
                        score = 2;
                    } else {
                        score = 1;
                    }
                } else if (name == "max") {
                    int numPieces = (int) getGameScene()->getGameBoard()->getPieces().size();
                    
                    int maximum = sublevel["objectives"][0]["quantity"].GetInt();
                    
                    float remainingPercentage = (float)numPieces / (float)maximum;
                    if (remainingPercentage < 0.7) {
                        score = 3;
                    } else if (remainingPercentage < 0.85) {
                        score = 2;
                    } else {
                        score = 1;
                    }
                }
                
                mScore = score;
                
                auto levelInfo = LevelInfo::getInstance();
                auto player = Player::getMainPlayer();
                
                mPointsEarned = 0;
                int oldScore = levelInfo->getLevelStatus(mLevelDesc->levelNum, mSublevel);
                if (oldScore < score) {
                    auto maxSublevel = mLevelDesc->data["sublevels"].Size() - 1;
                    int levelMultiplier = ceil((float)(mSublevel + 1) / 3.0f);
                    if (mSublevel == maxSublevel) {
                        levelMultiplier = 10;
                    }
                    
                    for (int i = 1; i <= kMaxScore; i++) {
                        if (oldScore < i && score >= i) {
                            mPointsEarned += kCurrencyPerScore[i-1] * levelMultiplier;
                            
                        }
                    }
                }
                
                player->addCurrency(mPointsEarned);
                
                LevelInfo::getInstance()->completeLevel(mLevelDesc->levelNum, mSublevel, score);
            }
        }
        
        GameMode::setGameState(state);
    }
    
    void LevelsGameMode::onBackPressed()
    {
        if (getGameState() == GameState::Paused) {
            resumeGame();
        } else if (getGameState() == GameState::InProgress) {
            pauseGame();
        } else {
            SceneManager::popSceneWithTransition<TransitionSlideInL>(kTransitionDuration);
        }
    }
    
    bool LevelsGameMode::isFinalLevel()
    {
        return mSublevel == mLevelDesc->data["sublevels"].Size() - 1;
    }
}
