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
            
        };
        addChild(hud);
        
        return true;
    }
    
    void MainMenuScene::onGameModeSelected(GameModeType type)
    {
        MainGameScene* gameScene = nullptr;
        
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
                
            default:
                break;
        }
        
        if (gameScene) {
            Director::getInstance()->pushScene(gameScene);
        }
    }
}