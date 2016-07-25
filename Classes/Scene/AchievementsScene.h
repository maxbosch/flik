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
#include "GUI/CCScrollView/CCTableView.h"
#include "GameServices.h"

namespace flik
{
    class AchievementsScene : public cocos2d::Scene, public cocos2d::extension::TableViewDataSource
    {
    public:
        CREATE_FUNC(AchievementsScene);
        
        bool init();
        
        /* TableViewDataSource */
        virtual cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
        virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
        virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
        
    private:
        TAchievementList mAchievements;
    };
};
