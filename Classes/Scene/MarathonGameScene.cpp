//
//  MarathonGameScene.cpp
//  Flik
//
//  Created by Adam Eskreis on 9/27/16.
//
//

#include "MarathonGameScene.h"
#include "MarathonGameMode.h"
#include "MainGameHUD.h"
#include "SceneManager.h"

namespace flik
{
    bool MarathonGameScene::init()
    {
        if (!MainGameScene::init({MarathonGameMode::create(), MainGameHUD::create()}))
        {
            return false;
        }
        
        return true;
    }
    
    void MarathonGameScene::reloadScene()
    {
        MainGameScene::reloadScene();
        
        auto scene = MarathonGameScene::create();
        SceneManager::replaceScene(scene);
    }
}
