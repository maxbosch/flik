//
//  ChoosePowerupScene.hpp
//  Flik
//
//  Created by Adam Eskreis on 9/20/16.
//
//

#pragma once

#include "cocos2d.h"
#include "Enums.h"
#include "SceneEx.h"
#include "GUI/CCScrollView/CCTableView.h"

namespace flik
{
    class BonusBar;
    
    class ChoosePowerupScene : public SceneEx, public cocos2d::extension::TableViewDataSource
    {
    public:
        static ChoosePowerupScene* create(const std::vector<BonusType>& currentBonuses, bool lockSelected = false);
        
        bool init(const std::vector<BonusType>& currentBonuses, bool lockSelected);
        
        void onBackPressed();
        void onAppear();
        std::function<void(const std::vector<BonusType>&)> onPowerupsChosen;
        
        /* TableViewDataSource */
        virtual cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
        virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
        virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
        
    private:
        std::vector<BonusType> mCurrentBonuses;
        BonusBar* mBonusBar;
        bool mLockSelected;
        cocos2d::extension::TableView* mPowerupsTable;
    };
}
