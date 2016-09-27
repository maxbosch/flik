//
//  LevelGameScene.cpp
//  Flik
//
//  Created by Adam Eskreis on 9/27/16.
//
//

#include "LevelGameScene.h"
#include "LevelTypes.h"
#include "LevelsGameMode.h"
#include "LevelsGameHUD.h"
#include "Util.h"
#include "SceneManager.h"

namespace flik
{
    LevelGameScene* LevelGameScene::create(const LevelDescription* levelDesc, int sublevel)
    {
        return createWithParams<LevelGameScene>(levelDesc, sublevel);
    }
    
    bool LevelGameScene::init(const LevelDescription* levelDesc, int sublevel)
    {
        auto gameMode = LevelsGameMode::create(levelDesc, sublevel);
        auto gameHUD = LevelsGameHUD::create(levelDesc);
        if (!MainGameScene::init({gameMode, gameHUD})) {
            return false;
        }
        
        mLevelDesc = levelDesc;
        mSublevel = sublevel;
        
        return true;
    }

    void LevelGameScene::reloadScene()
    {
        MainGameScene::reloadScene();
        
        auto scene = LevelGameScene::create(mLevelDesc, mSublevel);
        SceneManager::replaceScene(scene);
    }
}
