//
//  MainMenuHUD.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/2/16.
//
//

#include "MainMenuScene.h"
#include "Colors.h"

USING_NS_CC;

namespace flik
{
    cocos2d::Scene* MainMenuScene::createScene()
    {
        auto scene = Scene::create();
        
        // 'layer' is an autorelease object
        auto self = MainMenuScene::create();
        
        // add layer as a child to scene
        scene->addChild(self);

        // return the scene
        return scene;
    }
    
    bool MainMenuScene::init()
    {
        if (!Layer::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
        
        auto menuFrame = cocos2d::ui::RelativeBox::create(uiSize);
        menuFrame->setBackGroundColor(kBlackColor);
        menuFrame->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        
        return true;
    }
}