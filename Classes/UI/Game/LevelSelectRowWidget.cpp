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
#include "LocalizedString.h"
#include "format.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    LevelSelectRowWidget* LevelSelectRowWidget::create(int level, int sublevel)
    {
        return createWithParams<LevelSelectRowWidget>(level, sublevel);
    }
    
    bool LevelSelectRowWidget::init(int level, int sublevel)
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto levelText = Fonts::createLocalizedText(LocalizedString::getString("game_mode_level", sublevel + 1), 21.0_dp);
        auto levelTextLayout = ui::RelativeLayoutParameter::create();
        levelTextLayout->setAlign(RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
        levelTextLayout->setMargin(ui::Margin(37.0_dp, 0, 0, 0));
        levelText->setLayoutParameter(levelTextLayout);
        addChild(levelText);
        
        auto levelInfo = LevelInfo::getInstance();
        int levelStatus = levelInfo->getLevelStatus(level, sublevel);
        
        auto levelStatusContainer = ui::RelativeBox::create(Size(60.0_dp, 60.0_dp));
        auto levelStatusContainerLayout = ui::RelativeLayoutParameter::create();
        levelStatusContainerLayout->setAlign(RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
        levelStatusContainerLayout->setMargin(ui::Margin(0, 0, 37.0_dp, 0));
        levelStatusContainer->setLayoutParameter(levelStatusContainerLayout);
        addChild(levelStatusContainer);
        
        if (levelStatus < 1) {
            std::string image;
            double rightMargin = 0;
            if (levelStatus == -1) {
                image = "level_locked.png";
                rightMargin = 5.0_dp;
            } else if (levelStatus == 0) {
                image = "game_select_icon.png";
            }
            
            auto levelStatus = ui::ImageView::create(image);
            auto levelStatusLayout = ui::RelativeLayoutParameter::create();
            levelStatusLayout->setAlign(RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
            levelStatusLayout->setMargin(ui::Margin(0, 5.0_dp, rightMargin, 0));
            levelStatus->setLayoutParameter(levelStatusLayout);
            levelStatusContainer->addChild(levelStatus);
        } else {
            auto starSize = Size(20.0_dp, 19.0_dp);
            
            auto starContainer = ui::HBox::create(Size(starSize.width * levelStatus, starSize.height));
            auto starContainerLayout = ui::RelativeLayoutParameter::create();
            starContainerLayout->setAlign(RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
            starContainerLayout->setMargin(ui::Margin(0, 10.0_dp, 8.0_dp, 0));
            starContainer->setLayoutParameter(starContainerLayout);
            levelStatusContainer->addChild(starContainer);
            
            for (int i = 0; i < levelStatus; i++) {
                auto image = ui::ImageView::create("star.png");
                auto imageLayout = ui::LinearLayoutParameter::create();
                imageLayout->setMargin(ui::Margin(4.0_dp, 0, 0, 0));
                image->setLayoutParameter(imageLayout);
                starContainer->addChild(image);
            }
        }
        
        if (levelStatus == kMaxScore) {
            levelText->setColor(kYellowColor);
        }
        
        setTouchEnabled(true);
        addTouchEventListener([this, sublevel](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::BEGAN) {
                setBackGroundColor(Util::getColorFromHex("444444"));
                setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
            } else {
                if (type == TouchEventType::ENDED && onTapped) {
                    onTapped(sublevel);
                }
                
                setBackGroundColor(Util::getColorFromHex("000000"));
                setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::NONE);
            }
        });

        return true;
    }
}
