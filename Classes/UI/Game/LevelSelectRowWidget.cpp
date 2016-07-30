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
#include "format.h"

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
        
        auto levelText = Fonts::createLocalizedText("Level " + boost::lexical_cast<std::string>(level), 25.0_dp);
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
        
        /*std::string imageName = "level_locked.png";
        if (levelInfo->getMaxLevelCompleted() == level) {
            imageName = "level_current.png";
            levelText->setColor(Util::getColorFromHex("FACC89"));
        } else if (levelInfo->getMaxLevelCompleted() > level) {
            imageName = "level_complete.png";
            levelText->setColor(Util::getColorFromHex("FF00A1"));
        }
        auto levelStatus = ui::ImageView::create(imageName);
        auto levelStatusLayout = ui::RelativeLayoutParameter::create();
        levelStatusLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        levelStatus->setLayoutParameter(levelStatusLayout);
        levelStatusContainer->addChild(levelStatus);*/
        
        int sublevel = levelInfo->getSublevel(level);
        auto levelStatus = ui::Text::create(fmt::sprintf("%dx", sublevel),
                                            Fonts::getFontForString("0"), 18.0_dp);
        auto levelStatusLayout = ui::RelativeLayoutParameter::create();
        levelStatusLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        levelStatusLayout->setRelativeName("sublevel");
        levelStatusLayout->setMargin(ui::Margin(0.0, 25.0_dp, 0.0, 0.0));
        levelStatus->setLayoutParameter(levelStatusLayout);
        levelStatusContainer->addChild(levelStatus);
        
        auto starIcon = ui::ImageView::create("icon_rate_star.png");
        starIcon->setScale(0.75);
        auto starIconLayout = ui::RelativeLayoutParameter::create();
        starIconLayout->setRelativeToWidgetName("sublevel");
        starIconLayout->setAlign(RelativeAlign::LOCATION_RIGHT_OF_TOPALIGN);
        starIconLayout->setMargin(ui::Margin(-2.0_dp, -5.0_dp, 0.0, 0.0));
        starIcon->setLayoutParameter(starIconLayout);
        levelStatusContainer->addChild(starIcon);
        
        
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
