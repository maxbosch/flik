//
//  TransitionSlideOutR.cpp
//  Flik
//
//  Created by Adam Eskreis on 10/12/16.
//
//

#include "TransitionEx.h"

namespace cocos2d
{
#define ADJUST_FACTOR 0.5f
    TransitionSlideOutL::TransitionSlideOutL()
    {
    }
    
    TransitionSlideOutL::~TransitionSlideOutL()
    {
    }
    
    void TransitionSlideOutL::onEnter()
    {
        TransitionScene::onEnter();
        this->initScenes();
        
        ActionInterval *in = this->action();
        ActionInterval *out = this->action();
        
        ActionInterval* inAction = easeActionWithAction(in);
        ActionInterval* outAction = (ActionInterval*)Sequence::create
        (
         easeActionWithAction(out),
         CallFunc::create(CC_CALLBACK_0(TransitionScene::finish,this)),
         nullptr
         );
        _inScene->runAction(inAction);
        _outScene->runAction(outAction);
    }
    
    void TransitionSlideOutL::sceneOrder()
    {
        _isInSceneOnTop = true;
    }
    
    void TransitionSlideOutL:: initScenes()
    {
        Size s = Director::getInstance()->getWinSize();
        _inScene->setPosition((s.width-ADJUST_FACTOR),0);
    }
    
    ActionInterval* TransitionSlideOutL::action()
    {
        Size s = Director::getInstance()->getWinSize();
        return MoveBy::create(_duration, Vec2(-(s.width-ADJUST_FACTOR),0));
    }
    
    ActionInterval* TransitionSlideOutL::easeActionWithAction(ActionInterval* action)
    {
        return EaseOut::create(action, 2.0f);
    }
    
    TransitionSlideOutL* TransitionSlideOutL::create(float t, Scene* scene)
    {
        TransitionSlideOutL* newScene = new (std::nothrow) TransitionSlideOutL();
        if(newScene && newScene->initWithDuration(t, scene))
        {
            newScene->autorelease();
            return newScene;
        }
        CC_SAFE_DELETE(newScene);
        return nullptr;
    }
    
    TransitionSlideOutR::TransitionSlideOutR()
    {
    }
    TransitionSlideOutR::~TransitionSlideOutR()
    {
    }
    
    TransitionSlideOutR* TransitionSlideOutR::create(float t, Scene* scene)
    {
        TransitionSlideOutR* newScene = new (std::nothrow) TransitionSlideOutR();
        if(newScene && newScene->initWithDuration(t, scene))
        {
            newScene->autorelease();
            return newScene;
        }
        CC_SAFE_DELETE(newScene);
        return nullptr;
    }
    
    void TransitionSlideOutR::sceneOrder()
    {
        _isInSceneOnTop = true;
    }
    
    void TransitionSlideOutR::initScenes()
    {
        Size s = Director::getInstance()->getWinSize();
        _inScene->setPosition(-s.width-ADJUST_FACTOR,0);
    }
    
    
    ActionInterval* TransitionSlideOutR:: action()
    {
        Size s = Director::getInstance()->getWinSize();
        return MoveBy::create(_duration, Vec2((s.width-ADJUST_FACTOR),0));
    }
}
