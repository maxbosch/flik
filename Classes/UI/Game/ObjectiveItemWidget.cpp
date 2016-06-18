//
//  ObjectiveItemWidget.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/16/16.
//
//

#include <boost/lexical_cast.hpp>

#include "ObjectiveItemWidget.h"
#include "Util.h"
#include "Literals.h"
#include "Styles.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    ObjectiveItemWidget* ObjectiveItemWidget::create(const std::string& normalImage, const std::string& completedImage, int quantity)
    {
        return createWithParams<ObjectiveItemWidget>(normalImage, completedImage, quantity);
    }
    
    bool ObjectiveItemWidget::init(const std::string& normalImage, const std::string& completedImage, int quantity)
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto image = ui::ImageView::create(normalImage);
        auto imageLayout = ui::RelativeLayoutParameter::create();
        imageLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        image->setLayoutParameter(imageLayout);
        addChild(image);
        mImage = image;
        
        auto textContainer = ui::RelativeBox::create(Size(35.0_dp, 13.0_dp));
        textContainer->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        textContainer->setBackGroundColor(Color3B::BLACK);
        auto textContainerLayout = ui::RelativeLayoutParameter::create();
        textContainerLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        textContainerLayout->setMargin(ui::Margin(0, 9.0_dp, 0, 0));
        textContainer->setLayoutParameter(textContainerLayout);
        addChild(textContainer);
        
        auto text = ui::Text::create(boost::lexical_cast<std::string>(quantity), kDefaultFont, 11.0_dp);
        auto textLayout = ui::RelativeLayoutParameter::create();
        textLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        text->setLayoutParameter(textLayout);
        textContainer->addChild(text);
        mText = text;
        
        mQuantity = quantity;
        mCurrentCount = 0;
        mCompleted = false;
        
        mCompletedImage = completedImage;
        
        scheduleUpdate();
        
        return true;
    }
    
    void ObjectiveItemWidget::incrementObjective(int count)
    {
        mCurrentCount = std::min(mQuantity, mCurrentCount + count);
    }
    
    void ObjectiveItemWidget::update(float time)
    {
        Widget::update(time);
        
        if (!isComplete()) {
            int remaining = std::max(0, mQuantity - mCurrentCount);
            mText->setString(boost::lexical_cast<std::string>(remaining));
            if (remaining == 0) {
                mImage->loadTexture(mCompletedImage);
                mText->setVisible(false);
                mText->getParent()->setVisible(false);
                mCompleted = true;
            }
        }
    }
}