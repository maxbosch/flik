//
//  ObjectiveDisplayWidget.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/16/16.
//
//

#include "ObjectiveDisplayWidget.h"
#include "Util.h"
#include "Literals.h"
#include "ObjectiveItemWidget.h"
#include "LocalizedString.h"
#include "Fonts.h"

USING_NS_CC;

namespace flik
{
    static std::map<ObjectiveType, std::string> kObjectiveImages {
        std::pair<ObjectiveType, std::string>(ObjectiveType::CollectPiece, "objective_collect_red_piece.png")
    };
    
    static std::map<ObjectiveType, std::string> kObjectiveCompletedImages {
        std::pair<ObjectiveType, std::string>(ObjectiveType::CollectPiece, "objective_collect_red_piece_complete.png")
    };
    
    ObjectiveDisplayWidget* ObjectiveDisplayWidget::create(const std::vector<LevelObjective>& objectives)
    {
        return createWithParams<ObjectiveDisplayWidget>(objectives);
    }
    
    bool ObjectiveDisplayWidget::init(const std::vector<LevelObjective>& objectives)
    {
        if (!HBox::init())
        {
            return false;
        }
        
        Size contentSize(50.0_dp * objectives.size(), 80.0_dp);
        setContentSize(contentSize);
        
        /*for (auto& objective : objectives) {
            auto widget =
         
         
//        }*/
//        
//        auto widget =  ObjectiveItemWidget::create(kObjectiveImages[objectives[0].type], kObjectiveCompletedImages[objective.type], objective.quantity);
//        widget->setContentSize(Size(30.0_dp, 30.0_dp));
//        auto widgetLayout = ui::LinearLayoutParameter::create();
//        widgetLayout->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::TOP);
//        widgetLayout->setMargin(ui::Margin(8.0_dp, 10.0_dp, 8.0_dp, 0));
//        widget->setLayoutParameter(widgetLayout);
//        addChild(widget);

        
        //mObjectiveWidgets[objectives[0].type] = widget;
        
        return true;
    }
    
    void ObjectiveDisplayWidget::incrementObjective(ObjectiveType objective, int count)
    {
        auto widget = mObjectiveWidgets.find(objective);
        if (widget != mObjectiveWidgets.end()) {
            widget->second->incrementObjective(count);
        }
    }
}
