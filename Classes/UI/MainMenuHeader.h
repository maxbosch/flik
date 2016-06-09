//
//  MainMenuHeader.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/6/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class MainMenuHeader : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(MainMenuHeader);
        
        bool init();
    };
}
