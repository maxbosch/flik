//
//  OverlayBackgroundWidget.hpp
//  Flik
//
//  Created by Adam Eskreis on 10/19/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class OverlayBackgroundWidget : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(OverlayBackgroundWidget);
        
        bool init();
    };
}
