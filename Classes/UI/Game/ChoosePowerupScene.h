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
#include "ui/CocosGUI.h"

namespace flik
{
    class BonusBar;
    
    class ChoosePowerupScene : public SceneEx
    {
    public:
        static ChoosePowerupScene* create(const std::vector<BonusType>& currentBonuses, bool lockSelected = false);
        
        bool init(const std::vector<BonusType>& currentBonuses, bool lockSelected);
        
        void onBackPressed();
        void onAppear();
        std::function<void(const std::vector<BonusType>&)> onPowerupsChosen;
        
    private:
        std::vector<BonusType> mCurrentBonuses;
        std::vector<BonusType> mLockedBonuses;
        BonusBar* mBonusBar;
        bool mLockSelected;
        cocos2d::ui::ScrollView* mPowerupsTable;
        
        void refreshPowerupsTable();
    };
}
