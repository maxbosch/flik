//
//  OverlayBackgroundWidget.cpp
//  Flik
//
//  Created by Adam Eskreis on 10/19/16.
//
//

#include "OverlayBackgroundWidget.h"
#include "Styles.h"

USING_NS_CC;

namespace flik
{
    bool OverlayBackgroundWidget::init()
    {
        auto uiSize = Director::getInstance()->getVisibleSize();
        
        if (!RelativeBox::init())
        {
            return false;
        }
        
        setContentSize(uiSize);
        setBackGroundColor(Color3B::BLACK);
        setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        setOpacity(kOverlayBackgroundOpacity);
        
        addTouchEventListener([](Ref* sender, TouchEventType type) {
           // Just eat all touches
        });
        setTouchEnabled(true);
        
        return true;
    }
}
