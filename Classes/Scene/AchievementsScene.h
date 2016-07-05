//
//  AchievementsScene.hpp
//  Flik
//
//  Created by Adam Eskreis on 7/5/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/CCTableView.h"

namespace flik
{
    class AchievementsScene : public cocos2d::Scene, public cocos2d::ui::TableViewDataSource
    {
    public:
        CREATE_FUNC(AchievementsScene);
        
        bool init();
        
        /* TableViewDataSource */
        virtual Size cellSizeForTable(TableView *table);
        virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
        virtual ssize_t numberOfCellsInTableView(TableView *table);
    };
};
