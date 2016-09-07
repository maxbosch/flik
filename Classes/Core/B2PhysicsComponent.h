//
//  B2PhysicsComponent.hpp
//  Flik
//
//  Created by Adam Eskreis on 8/29/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    class B2PhysicsComponent : public cocos2d::Component
    {
    public:
        CREATE_FUNC(B2PhysicsComponent);
        
        void update(float delta);
    };
}