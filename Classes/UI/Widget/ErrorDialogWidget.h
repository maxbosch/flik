//
//  ErrorDialogWidget.hpp
//  Flik
//
//  Created by Adam Eskreis on 11/22/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class ErrorDialogWidget : public cocos2d::ui::RelativeBox
    {
    public:
        static ErrorDialogWidget* create(const std::string& title, const std::string& description);
        
        bool init(const std::string& title, const std::string& description);
        
        void show();
    };
}
