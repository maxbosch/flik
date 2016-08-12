//
//  MainMenuHUD.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/2/16.
//
//

#include "MainMenuScene.h"
#include "Styles.h"
#include "MainMenuHUD.h"
#include "MainGameScene.h"
#include "TimedGameMode.h"
#include "TimedGameHUD.h"
#include "MarathonGameMode.h"
#include "TimedGameMode.h"
#include "StoreScene.h"
#include "LevelsGameMode.h"
#include "LevelsGameHUD.h"
#include "LevelTypes.h"
#include "LevelSelectScene.h"
#include "SceneManager.h"

USING_NS_CC;

namespace flik
{
    bool MainMenuScene::init()
    {
        if (!Scene::init())
        {
            return false;
        }
        
        auto hud = MainMenuHUD::create();
        hud->onGameModeSelected = CC_CALLBACK_1(MainMenuScene::onGameModeSelected, this);
        hud->onShowStoreTapped = []() {
            auto storeScene = StoreScene::create();
            SceneManager::pushSceneWithTransition<TransitionSlideInB>(storeScene, kTransitionDuration);
        };
        addChild(hud);
        
        return true;
    }
    
    void MainMenuScene::onGameModeSelected(GameModeType type)
    {
        Scene* gameScene = nullptr;
        
        switch (type) {
            case GameModeType::Timed:
            {
                auto gameMode = TimedGameMode::create();
                gameMode->setGameTime(60);
                gameScene = MainGameScene::create({gameMode, TimedGameHUD::create()});
                break;
            }
                
            case GameModeType::Unlimited:
                gameScene = MainGameScene::create({MarathonGameMode::create(), MainGameHUD::create()});
                break;
                
            case GameModeType::Levels:
            {
                auto levelInfo = LevelInfo::getInstance();
                auto levelDesc = levelInfo->getLevelDescription(levelInfo->getMaxLevelCompleted());
                //gameScene = MainGameScene::create({LevelsGameMode::create(levelDesc), LevelsGameHUD::create(levelDesc)});
                gameScene = LevelSelectScene::create();
                break;
            }
                
            default:
                break;
        }
        
        
        if (gameScene) {
            SceneManager::pushSceneWithTransition<TransitionSlideInT>(gameScene, kTransitionDuration);
        }
    }
    
    void MainMenuScene::onBackPressed()
    {
        Director::getInstance()->end();
    }
}