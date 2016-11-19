//
//  StorePurchaseOptionWidget.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/10/16.
//
//

#include <boost/lexical_cast.hpp>
#include <iomanip>

#include "StorePurchaseOptionWidget.h"
#include "Literals.h"
#include "Styles.h"
#include "Util.h"
#include "Player.h"
#include "LocalizedString.h"
#include "GameServices.h"

#include "Analytics.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    StorePurchaseOptionWidget* StorePurchaseOptionWidget::create(int pointsCount, float cost, const std::string& productName)
    {
        return createWithParams<StorePurchaseOptionWidget>(pointsCount, cost, productName);
    }
    
    bool StorePurchaseOptionWidget::init(int pointsCount, float cost, const std::string& productName)
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        setContentSize(Size(118.5_dp, 65.0_dp));
        
        auto label = Fonts::createLocalizedText(LocalizedString::getString("store_points", pointsCount), 15.0_dp);
        label->setTextColor(Color4B::WHITE);
        auto labelLayout = ui::RelativeLayoutParameter::create();
        labelLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        label->setLayoutParameter(labelLayout);
        addChild(label);
        
        auto purchaseButton = ui::Button::create("purchase_button.png");
        Fonts::updateLocalizedText(purchaseButton, Util::toMoneyValue(cost));
        purchaseButton->setTitleFontName(Fonts::getFontForString(purchaseButton->getTitleText()));
        purchaseButton->setTitleFontSize(15.0_dp);
        purchaseButton->setTitleColor(Util::getColorFromHex("FACC89"));
        purchaseButton->getTitleRenderer()->setPosition(purchaseButton->getTitleRenderer()->getPosition() - Vec2(0, 2.0_dp));
        auto purchaseButtonLayout = ui::RelativeLayoutParameter::create();
        purchaseButtonLayout->setAlign(RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
        purchaseButton->setLayoutParameter(purchaseButtonLayout);
        addChild(purchaseButton);
        
        purchaseButton->addTouchEventListener([this, pointsCount, cost, productName](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::ENDED) {
                GameServices::getInstance()->purchaseProduct(productName, [pointsCount](const sdkbox::Product& p, bool success, const std::string& msg) {
                    if (success) {
                        auto player = Player::getMainPlayer();
                        if (player->getCurrencyAmount() + pointsCount < kMaxCurrencyAmount) {
                            player->addCurrency(pointsCount);
                        }
                    } else {
                        // No-op for now
                    }
                    
                    PTree attributes;
                    attributes.add("quantity", pointsCount);
                    attributes.add("product_sku", "");
                    attributes.add("purchased", (int)success);
                    Analytics::logEvent("store_buy_points", attributes);
                }); 
            }
        });
        
        return true;
    }
}
