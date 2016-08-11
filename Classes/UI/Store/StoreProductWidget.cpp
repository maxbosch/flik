//
//  StoreProductWidget.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/9/16.
//
//

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "StoreProductWidget.h"
#include "Literals.h"
#include "PowerUpButton.h"
#include "Styles.h"
#include "Util.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    static std::string kProductTextFormat = "%d %s";
    
    StoreProductWidget* StoreProductWidget::create(PowerUpType type, int cost, int quantity, const std::string& productName)
    {
        return createWithParams<StoreProductWidget>(type, cost, quantity, productName);
    }
    
    bool StoreProductWidget::init(PowerUpType type, int cost, int quantity, const std::string& productName)
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        setContentSize(Size(120.0_dp, 200.0_dp));
        
        auto button = PowerUpButton::create(type);
        button->setEnabled(false);
        auto buttonLayout = ui::RelativeLayoutParameter::create();
        buttonLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        buttonLayout->setMargin(ui::Margin(0, 25.0_dp, 0, 0));
        button->setLayoutParameter(buttonLayout);
        addChild(button);
        
        auto circleShape = ui::ImageView::create("purchase_default.png");
        auto circleShapeLayout = ui::RelativeLayoutParameter::create();
        circleShapeLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        circleShapeLayout->setRelativeName("circle");
        circleShape->setLayoutParameter(circleShapeLayout);
        addChild(circleShape);
        
        std::stringstream productText;
        productText << quantity << " " << boost::to_upper_copy(productName);
        auto productLabel = Fonts::createLocalizedText(productText.str(), 15.0_dp);
        productLabel->setTextColor(Color4B::WHITE);
        auto productLabelLayout = ui::RelativeLayoutParameter::create();
        productLabelLayout->setRelativeToWidgetName("circle");
        productLabelLayout->setRelativeName("product_text");
        productLabelLayout->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
        productLabelLayout->setMargin(ui::Margin(0, 25.0_dp, 0, 0));
        productLabel->setLayoutParameter(productLabelLayout);
        addChild(productLabel);
        
        auto purchaseButton = ui::Button::create("purchase_button.png");
        Fonts::updateLocalizedText(purchaseButton, boost::lexical_cast<std::string>(cost));
        purchaseButton->setTitleFontName(Fonts::getFontForString(purchaseButton->getTitleText()));
        purchaseButton->setTitleFontSize(15.0_dp);
        purchaseButton->setTitleColor(Util::getColorFromHex("FACC89"));
        purchaseButton->getTitleRenderer()->setPosition(purchaseButton->getTitleRenderer()->getPosition() - Vec2(0, 2.0_dp));
        auto purchaseButtonLayout = ui::RelativeLayoutParameter::create();
        purchaseButtonLayout->setRelativeToWidgetName("product_text");
        purchaseButtonLayout->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
        purchaseButtonLayout->setMargin(ui::Margin(0, 10.0_dp, 0, 0));
        purchaseButton->setLayoutParameter(purchaseButtonLayout);
        addChild(purchaseButton);
        
        purchaseButton->addTouchEventListener([this, type, cost, quantity](Ref* sender, TouchEventType eventType) {
            if (eventType == TouchEventType::ENDED && onProductPurchaseRequested) {
                onProductPurchaseRequested(type, cost, quantity);
            }
        });
        
        return true;
    }
}
