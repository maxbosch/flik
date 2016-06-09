//
//  MainMenuFooter.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/9/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class MainMenuFooter : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(MainMenuFooter);
        
        bool init();
        
        std::function<void()> onShowStoreTapped;
    };
}
