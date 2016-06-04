//
//  WidgetHelper.hpp
//  Fling
//
//  Created by Adam Eskreis on 5/31/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    class NodeHelper
    {
        static cocos2d::Node* findChildByName(cocos2d::Node* node, const std::string& name);
    };
};
