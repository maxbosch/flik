//
//  ObjectiveDisplayWidget.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/16/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "LevelTypes.h"

namespace flik
{
    class ObjectiveItemWidget;
    
    class ObjectiveDisplayWidget : public cocos2d::ui::HBox
    {
    public:
        static ObjectiveDisplayWidget* create(const std::vector<LevelObjective>& objectives);
        
        bool init(const std::vector<LevelObjective>& objectives);
        
        void incrementObjective(ObjectiveType objective, int count);
        
    private:
        std::map<ObjectiveType, ObjectiveItemWidget*> mObjectiveWidgets;
    };
}