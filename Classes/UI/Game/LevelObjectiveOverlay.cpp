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
        std::string text = "";
        switch (objective.type) {
            case ObjectiveType::ClearBoard:
                text = "objective_clear_board";
                break;
                
            case ObjectiveType::CollectPiece:
                text = "objective_collect_piece";
                break;
                
            default:
                break;
        }
        auto widget = Fonts::createLocalizedText(LocalizedString::getString(text, objective.quantity), 25.0_dp);
        widget->setColor(kGoldColor);
        widget->setTextAreaSize(Size(250.0_dp, 80.0_dp));
        widget->setTextHorizontalAlignment(TextHAlignment::CENTER);
        return widget;
    }
}