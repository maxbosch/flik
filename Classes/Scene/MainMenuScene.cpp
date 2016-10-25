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
#include "TimedGameScene.h"
#include "MarathonGameScene.h"
#include "TimedGameMode.h"
#include "StoreScene.h"
#include "LevelsGameMode.h"
#include "LevelsGameHUD.h"
#include "LevelTypes.h"
#include "GameSelectScene.h"
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
        hud->animateElements();
        
        return true;
    }
    
    void MainMenuScene::onGameModeSelected(GameModeType type)
    {
        Scene* gameScene = nullptr;
        
        switch (type) {
            case GameModeType::Timed:
            {
                gameScene = TimedGameScene::create();
                break;
            }
                
            case GameModeType::Unlimited:
                gameScene = MarathonGameScene::create();
                break;
                
            case GameModeType::Levels:
            {
                gameScene = GameSelectScene::create();
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
