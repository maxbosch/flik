//
//  BehaviorTypes.h
//  Flik
//
//  Created by Adam Eskreis on 8/4/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class MainGameScene;
    
    class Behavior : public cocos2d::Node
    {
    public:
        virtual bool init(MainGameScene* scene, float duration);
        
    protected:
        MainGameScene* getGameScene() { return mGameScene; }
        
        virtual void onExpire(MainGameScene* scene);
        
    private:
        MainGameScene* mGameScene;
    };
}
