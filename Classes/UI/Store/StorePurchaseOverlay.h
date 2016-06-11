//
//  StorePurchaseOverlay.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/10/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class StorePurchaseOverlay : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(StorePurchaseOverlay);
        
        bool init();
    };
}
