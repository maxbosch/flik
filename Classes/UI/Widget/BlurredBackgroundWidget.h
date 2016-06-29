//
//  BlurredBackgroundWidget.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/21/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class BlurredBackgroundWidget : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(BlurredBackgroundWidget);
        
        bool init();
    };
}