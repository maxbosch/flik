//
//  WidgetHelper.cpp
//  Fling
//
//  Created by Adam Eskreis on 5/31/16.
//
//

#include "NodeHelper.h"

namespace flik
{
    cocos2d::Node* NodeHelper::findChildByName(cocos2d::Node* node, const std::string& name)
    {
        if (node->getName() == name) {
            return node;
        }
        
        //node->enumerateChildren(<#const std::string &name#>, <#std::function<bool (Node *)> callback#>)
    }
}
