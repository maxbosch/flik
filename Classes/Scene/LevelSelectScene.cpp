//
//  LevelSelectScene.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/20/16.
//
//

#include "LevelSelectScene.h"
#include "LevelSelectOverlay.h"
#include "SceneManager.h"
#include "Styles.h"

USING_NS_CC;

namespace flik
{
    bool LevelSelectScene::init()
    {
        if (!Scene::init())
        {
            return false;
        }
        
        auto levelSelectOverlay = LevelSelectOverlay::create();
        addChild(levelSelectOverlay);
        
        levelSelectOverlay->onExitButtonTapped = []() {
            SceneManager::popToRootSceneWithTransition<TransitionSlideInB>(kTransitionDuration);
        };
        
        return true;
    }
}