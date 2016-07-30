//
//  LevelObjectiveOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/16/16.
//
//

#include "LevelObjectiveOverlay.h"
#include "Util.h"
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
        auto& level = mLevelDesc->data["sublevels"][mLevelDesc->sublevelNum];
        auto& objectives = level["objectives"];
        auto& objective = objectives[0];
        std::string text = "objective_" + std::string(objective["type"].GetString());
        
        auto widget = Fonts::createLocalizedText(LocalizedString::getString(text, objective["quantity"].GetInt()), 25.0_dp);
        widget->setColor(kGoldColor);
        widget->setTextAreaSize(Size(250.0_dp, 80.0_dp));
        widget->setTextHorizontalAlignment(TextHAlignment::CENTER);
        return widget;
    }
}