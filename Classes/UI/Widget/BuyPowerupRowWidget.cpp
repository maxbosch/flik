//
//  BuyPowerupRowWidget.cpp
//  Flik
//
//  Created by Adam Eskreis on 9/27/16.
//
//

#include "BuyPowerupRowWidget.h"
#include <boost/lexical_cast.hpp>
#include "Literals.h"
#include "Util.h"
#include "Enums.h"
#include "Fonts.h"
USING_NS_CC;

namespace flik
{
    void BuyPowerupRowWidget::setData(BonusType type, bool selected)
    {
        ChoosePowerupRowWidget::setData(type, selected);
        
        int cost = kBonusCosts[type];
        
        auto buyButton = this->getAddButton();
        buyButton->loadTextureNormal("purchase_button.png");
        Fonts::updateLocalizedText(buyButton, boost::lexical_cast<std::string>(cost));
        buyButton->setTitleFontSize(15.0_dp);
        buyButton->setTitleColor(Util::getColorFromHex("FACC89"));
        
        buyButton->addTouchEventListener([this, type, cost](Ref* sender, ui::Widget::TouchEventType eventType) {
            if (eventType == ui::Widget::TouchEventType::ENDED && onBuyItemRequested) {
                onBuyItemRequested(type, cost);
            }
        });
    }
}
