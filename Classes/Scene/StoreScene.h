//
//  StoreScene.hpp
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
    class StorePurchaseOverlay;
    
    class StoreScene : public cocos2d::Scene
    {
    public:
        CREATE_FUNC(StoreScene);
        
        bool init();
        
        void update(float seconds);
    
    private:
        void setPurchaseOverlayVisible(bool visible);
        void onProductPurchaseRequested(PowerUpType type, int cost, int quantity);
        
        StorePurchaseOverlay* mPurchaseOverlay;
        cocos2d::ui::Button* mCloseButton;
        cocos2d::ui::Button* mPointsButton;
    };
}
