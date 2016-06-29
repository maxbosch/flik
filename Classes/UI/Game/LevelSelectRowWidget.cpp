//
//  LevelSelectRowWidget.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/20/16.
//
//

#include "LevelSelectRowWidget.h"
#include "Util.h"
#include "Styles.h"
#include "Literals.h"
#include "LevelTypes.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    LevelSelectRowWidget* LevelSelectRowWidget::create(int level)
    {
        return createWithParams<LevelSelectRowWidget>(level);
    }
    
    bool LevelSelectRowWidget::init(int level)
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto levelText = ui::Text::create("Level " + boost::lexical_cast<std::string>(level), kDefaultFont, 25.0_dp);
        auto levelTextLayout = ui::RelativeLayoutParameter::create();
        levelTextLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        levelTextLayout->setMargin(ui::Margin(37.0_dp, 22.0_dp, 0, 0));
        levelText->setLayoutParameter(levelTextLayout);
        addChild(levelText);
        
        auto levelInfo = LevelInfo::getInstance();
        
        auto levelStatusContainer = ui::RelativeBox::create(Size(60.0_dp, 60.0_dp));
        auto levelStatusContainerLayout = ui::RelativeLayoutParameter::create();
        levelStatusContainerLayout->setAlign(RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
        levelStatusContainerLayout->setMargin(ui::Margin(0, 0, 37.0_dp, 0));
        levelStatusContainer->setLayoutParameter(levelStatusContainerLayout);
        addChild(levelStatusContainer);
        
        std::string imageName = "level_locked.png";
        if (levelInfo->getMaxLevelCompleted() == level - 1) {
            imageName = "level_current.png";
            levelText->setColor(Util::getColorFromHex("FACC89"));
        } else if (levelInfo->getMaxLevelCompleted() > level - 1) {
            imageName = "level_complete.png";
            levelText->setColor(Util::getColorFromHex("FF00A1"));
        }
        auto levelStatus = ui::ImageView::create(imageName);
        auto levelStatusLayout = ui::RelativeLayoutParameter::create();
        levelStatusLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        levelStatus->setLayoutParameter(levelStatusLayout);
        levelStatusContainer->addChild(levelStatus);
        
        setTouchEnabled(true);
        addTouchEventListener([this, level](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::BEGAN) {
                setBackGroundColor(Util::getColorFromHex("444444"));
                setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
            } else {
                if (type == TouchEventType::ENDED && onTapped) {
                    onTapped(level);
                }
                
                setBackGroundColor(Util::getColorFromHex("000000"));
                setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::NONE);
            }
        });

        return true;
    }
}
