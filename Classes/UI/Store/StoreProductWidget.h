//
//  StoreProductWidget.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/9/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Enums.h"

namespace flik
{
    class StoreProductWidget : public cocos2d::ui::RelativeBox
    {
    public:
        static StoreProductWidget* create(PowerUpType type, int cost, int quantity, const std::string& productName);
        
        bool init(PowerUpType type, int cost, int quantity, const std::string& productName);
        
        std::function<void(PowerUpType, int, int)> onProductPurchaseRequested;
    };
}