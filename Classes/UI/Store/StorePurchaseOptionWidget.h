//
//  StorePurchaseOptionWidget.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/10/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class StorePurchaseOptionWidget : public cocos2d::ui::RelativeBox
    {
    public:
        static StorePurchaseOptionWidget* create(int pointsCount, float cost, const std::string& productName);
        
        bool init(int pointsCount, float cost, const std::string& productName);
    };
}