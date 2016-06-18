//
//  LevelObjectiveOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/16/16.
//
//

#include "LevelObjectiveOverlay.h"
#include "Util.h"
#include "ObjectiveDisplayWidget.h"
#include "LevelTypes.h"

USING_NS_CC;

namespace flik
{
    LevelObjectiveOverlay* LevelObjectiveOverlay::create(const std::string& title, const LevelDescription* levelDesc)
    {
        return createWithParams<LevelObjectiveOverlay>(title, levelDesc);
    }
    
    bool LevelObjectiveOverlay::init(const std::string& title, const LevelDescription* levelDesc)
    {
        mLevelDesc = levelDesc;
        
        return GameObjectiveOverlay::init(title);
    }
    
    ui::Widget* LevelObjectiveOverlay::createObjectiveWidget()
    {
        auto widget = ObjectiveDisplayWidget::create(mLevelDesc->objectives);
        return widget;
    }
}