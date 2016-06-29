//
//  LevelSelectOverlay.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/20/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class LevelSelectOverlay : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(LevelSelectOverlay);
        
        bool init();
        
        std::function<void()> onExitButtonTapped;
    };
}
