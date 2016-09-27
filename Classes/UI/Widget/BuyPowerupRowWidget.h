//
//  BuyPowerupRowWidget.hpp
//  Flik
//
//  Created by Adam Eskreis on 9/27/16.
//
//

#pragma once

#include "ChoosePowerupRowWidget.h"

namespace flik
{
    class BuyPowerupRowWidget : public ChoosePowerupRowWidget
    {
    public:
        CREATE_FUNC(BuyPowerupRowWidget);

        void setData(BonusType type, bool selected);
        
        std::function<void(BonusType type, int value)> onBuyItemRequested;
    };
}
