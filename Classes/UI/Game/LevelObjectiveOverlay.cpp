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
#include "Fonts.h"
#include "Styles.h"
#include "LocalizedString.h"
#include "Literals.h"

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
        //auto widget = ObjectiveDisplayWidget::create(mLevelDesc->objectives);
        auto objective = mLevelDesc->objectives[0];
        auto widget = Fonts::createLocalizedText(LocalizedString::getString("objective_clear_pieces", objective.quantity), 25.0_dp);
        widget->setColor(kGoldColor);
        widget->setTextAreaSize(Size(250.0_dp, 80.0_dp));
        widget->setTextHorizontalAlignment(TextHAlignment::CENTER);
        return widget;
    }
}