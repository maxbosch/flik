//
//  DialogMessage.hpp
//  Flik
//
//  Created by Adam Eskreis on 8/3/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class DialogMessage : public cocos2d::ui::RelativeBox
    {
    public:
        static DialogMessage* create(const std::string& title, const std::string& message);
        
        bool init(const std::string& title, const std::string& message);
        
        std::function<void()> onDismiss;
    };
}
