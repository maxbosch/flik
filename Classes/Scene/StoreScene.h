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
#include "SceneEx.h"
#include "GUI/CCScrollView/CCTableView.h"

namespace flik
{
    class StorePurchaseOverlay;
    
    class StoreScene : public SceneEx
    {
    public:
        CREATE_FUNC(StoreScene);
        
        bool init();
        
        void update(float seconds);
        
        void onBackPressed();
        
    private:
        void setPurchaseOverlayVisible(bool visible, bool animated = true);
        void onProductPurchaseRequested(PowerUpType type, int cost, int quantity);
        
        StorePurchaseOverlay* mPurchaseOverlay;
        cocos2d::ui::Button* mCloseButton;
        cocos2d::ui::Button* mPointsButton;
        cocos2d::ui::Widget* mProductsContainer;
        cocos2d::ui::ScrollView* mProductsTable;
        
        void refreshProductsTable();
    };
}
