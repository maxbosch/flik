//
//  ObjectiveProgress.h
//  Flik
//
//  Created by Adam Eskreis on 7/28/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    class ObjectiveTracker : public cocos2d::Node
    {
    public:
        virtual int getCurrentValue() = 0;
        virtual int getTotalValue() = 0;
        
        virtual bool isCompleted() = 0;
        virtual bool isFailed() = 0;
        
        virtual bool finishWhenComplete() = 0;
        
        virtual void reset() = 0;
    };
}
