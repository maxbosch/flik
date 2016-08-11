//
//  Behavior.cpp
//  Flik
//
//  Created by Adam Eskreis on 8/4/16.
//
//

#include "Behavior.h"
#include "format.h"

USING_NS_CC;

namespace flik
{
    bool Behavior::init(MainGameScene* scene, float duration)
    {
        if (!Node::init())
        {
            return false;
        }
        
        mGameScene = scene;
        
        scheduleOnce([this](float time) {
            this->onExpire(mGameScene);
            
            this->removeFromParent();
        }, duration, fmt::sprintf("behavior_duration_%d", rand()));
        
        scheduleUpdate();
        
        return true;
    }
    
    void Behavior::onExpire(MainGameScene* scene)
    {
    }
}
