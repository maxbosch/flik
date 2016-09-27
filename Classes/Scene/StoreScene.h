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
    
    class StoreScene : public SceneEx, public cocos2d::extension::TableViewDataSource
    {
    public:
        CREATE_FUNC(StoreScene);
        
        bool init();
        
        void update(float seconds);
        
        void onBackPressed();
    
        /* TableViewDataSource */
        virtual cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
        virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
        virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
        
    private:
        void setPurchaseOverlayVisible(bool visible, bool animated = true);
        void onProductPurchaseRequested(PowerUpType type, int cost, int quantity);
        
        StorePurchaseOverlay* mPurchaseOverlay;
        cocos2d::ui::Button* mCloseButton;
        cocos2d::ui::Button* mPointsButton;
        cocos2d::ui::Widget* mProductsContainer;
    };
}
