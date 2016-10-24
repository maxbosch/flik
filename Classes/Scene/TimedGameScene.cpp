//
//  TimedGameScene.cpp
//  Flik
//
//  Created by Adam Eskreis on 9/27/16.
//
//

#include "TimedGameScene.h"
#include "TimedGameMode.h"
#include "TimedGameHUD.h"
#include "SceneManager.h"

namespace flik
{
    bool TimedGameScene::init()
    {
        auto gameMode = TimedGameMode::create();
        gameMode->setGameTime(45);
        
        if (!MainGameScene::init({gameMode, TimedGameHUD::create()}))
        {
            return false;
        }
        
        return true;
    }
    
    void TimedGameScene::reloadScene()
    {
        MainGameScene::reloadScene();
        
        auto scene = TimedGameScene::create();
        SceneManager::replaceScene(scene);
    }
}
