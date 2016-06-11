//
//  StorePurchaseOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/10/16.
//
//

#include "StorePurchaseOverlay.h"
#include "Literals.h"
#include "Styles.h"
#include "StorePurchaseOptionWidget.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    bool StorePurchaseOverlay::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        setContentSize(Size(305.0_dp, 475.0_dp));
        
        auto backgroundImage = ui::ImageView::create("purchase_border.png");
        backgroundImage->setPosition(Vec2(0, 0));
        backgroundImage->setAnchorPoint(Vec2(0, 0));
        addChild(backgroundImage);
        
        auto titleLabel = ui::Text::create("MORE POINTS NEEDED", kDefaultFont, 18.0_dp);
        titleLabel->setColor(Color3B::WHITE);
        auto titleLabelLayout = ui::RelativeLayoutParameter::create();
        titleLabelLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        titleLabelLayout->setMargin(ui::Margin(0, 44.0_dp, 0, 0));
        titleLabelLayout->setRelativeName("title");
        titleLabel->setLayoutParameter(titleLabelLayout);
        addChild(titleLabel);
        
        auto subtitleLabel = ui::Text::create("Play more games to get more \npoints or purchase some below", kDefaultFont, 15.0_dp);
        subtitleLabel->setColor(Color3B::WHITE);
        subtitleLabel->setTextHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
        subtitleLabel->setContentSize(Size(250.0_dp, 40.0_dp));
        auto subtitleLabelLayout = ui::RelativeLayoutParameter::create();
        subtitleLabelLayout->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
        subtitleLabelLayout->setMargin(ui::Margin(0, 20.0_dp, 0, 0));
        subtitleLabelLayout->setRelativeToWidgetName("title");
        subtitleLabelLayout->setRelativeName("subtitle");
        subtitleLabel->setLayoutParameter(subtitleLabelLayout);
        addChild(subtitleLabel);
        
        auto productsList = ui::VBox::create();
        auto productsListLayout = ui::RelativeLayoutParameter::create();
        productsListLayout->setRelativeToWidgetName("subtitle");
        productsListLayout->setMargin(ui::Margin(0, 20.0_dp, 0, 0));
        productsListLayout->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
        productsList->setLayoutParameter(productsListLayout);
        addChild(productsList);
        
        std::vector<std::pair<int, float>> purchaseOptions {
            std::pair<int, float>(5000, 0.99),
            std::pair<int, float>(15000, 1.99),
            std::pair<int, float>(50000, 4.99)
        };
        
        Size productsListSize;
        for (auto& purchaseOption : purchaseOptions) {
            auto optionWidget = StorePurchaseOptionWidget::create(purchaseOption.first, purchaseOption.second);
            auto optionWidgetLayout = ui::LinearLayoutParameter::create();
            optionWidgetLayout->setMargin(ui::Margin(0, 25.0_dp, 0, 0));
            optionWidget->setLayoutParameter(optionWidgetLayout);
            productsList->addChild(optionWidget);
            
            productsListSize.width = std::max(optionWidget->getContentSize().width, productsListSize.width);
            productsListSize.height = std::max(optionWidget->getBoundingBox().getMaxY(), productsListSize.height);
        }
        
        productsList->setContentSize(productsListSize);
        
        
        
        
        return true;
    }
}