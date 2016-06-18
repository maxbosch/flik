//
//  TextObjectiveOverlay.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/15/16.
//
//

#pragma once

#include "cocos2d.h"
#include "GameObjectiveOverlay.h"

namespace flik
{
    class TextObjectiveOverlay : public GameObjectiveOverlay
    {
    public:
        static TextObjectiveOverlay* create(const std::string& title, const std::string& text);
        
        cocos2d::ui::Widget* createObjectiveWidget();
        
        bool init(const std::string& title, const std::string& text);
        
    private:
        std::string mText;
    };
}