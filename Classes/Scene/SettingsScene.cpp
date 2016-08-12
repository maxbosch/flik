//
//  SettingsScene.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/23/16.
//
//

#include "SettingsScene.h"
#include "ui/CocosGUI.h"
#include "Styles.h"
#include "Literals.h"
#include "Util.h"
#include "PlatformUtil.h"
#include "SceneManager.h"
#include "LocalizedString.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    static const std::string kSoundsEnabledKey = "key_soundsEnabled";
    static const std::string kVibrationsEnabledKey = "key_vibrationsEnabled";
    
    bool SettingsScene::init()
    {
        if (!Scene::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);
        
        auto container = ui::VBox::create(uiSize);
        container->setBackGroundColor(kGreenColor);
        container->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        container->setPosition(Vec2());
        container->setAnchorPoint(Vec2());
        container->setContentSize(uiSize);
        addChild(container);
        
        auto header = ui::RelativeBox::create(Size(uiSize.width, 82.5_dp));
        container->addChild(header);
        
        auto title = Fonts::createLocalizedText(LocalizedString::getString("title_settings"), 25.0_dp);
        title->setTextVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        auto titleLayout = ui::RelativeLayoutParameter::create();
        titleLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        titleLayout->setMargin(ui::Margin(0, 29.0_dp, 0, 0));
        title->setLayoutParameter(titleLayout);
        header->addChild(title);
        
        auto backButton = ui::Button::create("arrow_left.png");
        auto backButtonLayout = ui::RelativeLayoutParameter::create();
        backButtonLayout->setAlign(RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
        backButtonLayout->setMargin(ui::Margin(20.0_dp, 0, 0, 0));
        backButton->setLayoutParameter(backButtonLayout);
        header->addChild(backButton);
        
        backButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                SceneManager::popSceneWithTransition<TransitionSlideInL>(kTransitionDuration);
            }
        });
        
        auto borderColor = Util::getColorFromHex("2D8253");
        
        auto border = ui::HBox::create(Size(uiSize.width, 0.5_dp));
        border->setBackGroundColor(borderColor);
        border->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
//        auto borderLayout = ui::RelativeLayoutParameter::create();
//        borderLayout->setAlign(RelativeAlign::PARENT_LEFT_BOTTOM);
//        border->setLayoutParameter(borderLayout);
        container->addChild(border);
        
        auto createCheckboxWidget = [&](const std::string& label, const std::string& key, bool defaultValue) -> ui::Widget* {
            auto checkboxContainer = ui::RelativeBox::create(Size(uiSize.width, 75.0_dp));
            checkboxContainer->setTouchEnabled(false);
            
            auto title = Fonts::createLocalizedText(label, 20.0_dp);
            title->setTextVerticalAlignment(cocos2d::TextVAlignment::CENTER);
            auto titleLayout = ui::RelativeLayoutParameter::create();
            titleLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
            titleLayout->setMargin(ui::Margin(21.0_dp, 27.5_dp, 0, 0));
            title->setLayoutParameter(titleLayout);
            checkboxContainer->addChild(title);
            
            auto checkbox = ui::CheckBox::create("checkbox_off.png", "checkbox_on.png", "", "", "");
            auto checkboxLayout = ui::RelativeLayoutParameter::create();
            checkboxLayout->setAlign(RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
            checkboxLayout->setMargin(ui::Margin(0, 0, 21.0_dp, 0));
            checkbox->setLayoutParameter(checkboxLayout);
            checkboxContainer->addChild(checkbox);
            checkbox->setEnabled(UserDefault::getInstance()->getBoolForKey(key.c_str(), defaultValue));
            checkbox->setTouchEnabled(true);
            
            checkbox->addTouchEventListener([checkbox, key](Ref* sender, ui::Widget::TouchEventType type) {
                if (type == ui::Widget::TouchEventType::ENDED) {
                    UserDefault::getInstance()->setBoolForKey(key.c_str(), checkbox->isSelected());
                }
            });

            auto border = ui::HBox::create(Size(uiSize.width, 0.5_dp));
            border->setBackGroundColor(borderColor);
            border->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
            auto borderLayout = ui::RelativeLayoutParameter::create();
            borderLayout->setAlign(RelativeAlign::PARENT_LEFT_BOTTOM);
            border->setLayoutParameter(borderLayout);
            checkboxContainer->addChild(border);
            
            return checkboxContainer;
        };
        
        container->addChild(createCheckboxWidget(LocalizedString::getString("setting_sounds"), kSoundsEnabledKey, true));
        container->addChild(createCheckboxWidget(LocalizedString::getString("setting_vibrations"), kVibrationsEnabledKey, true));
        
        auto createLinkWidget = [&](const std::string& icon, const std::string& label, std::function<void()> callback) -> ui::Widget*{
            auto linkContainer = ui::RelativeBox::create(Size(uiSize.width, 60.0_dp));
        
            auto iconWidget = ui::ImageView::create(icon);
            auto iconWidgetLayout = ui::RelativeLayoutParameter::create();
            iconWidgetLayout->setAlign(RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
            iconWidgetLayout->setMargin(ui::Margin(22.0_dp, 0, 0, 0));
            iconWidgetLayout->setRelativeName("icon");
            iconWidget->setLayoutParameter(iconWidgetLayout);
            linkContainer->addChild(iconWidget);
            
            auto labelWidget = Fonts::createLocalizedText(label, 15.0_dp);
            auto labelLayout = ui::RelativeLayoutParameter::create();
            labelLayout->setAlign(RelativeAlign::LOCATION_RIGHT_OF_TOPALIGN);
            labelLayout->setMargin(ui::Margin(22.0_dp, 6.0_dp, 0, 0));
            labelLayout->setRelativeToWidgetName("icon");
            labelWidget->setLayoutParameter(labelLayout);
            linkContainer->addChild(labelWidget);
            
            auto chevron = ui::ImageView::create("chevron_right.png");
            auto chevronLayout = ui::RelativeLayoutParameter::create();
            chevronLayout->setAlign(RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
            chevronLayout->setMargin(ui::Margin(0, 0, 22.0_dp, 0));
            chevron->setLayoutParameter(chevronLayout);
            linkContainer->addChild(chevron);
            
            linkContainer->addTouchEventListener([callback](Ref* sender, ui::Widget::TouchEventType type) {
                if (type == ui::Widget::TouchEventType::ENDED && callback) {
                    callback();
                }
            });
            linkContainer->setTouchEnabled(true);
            
            return linkContainer;
        };
        
        container->addChild(createLinkWidget("icon_rate_star.png", LocalizedString::getString("setting_rate_us"), []() {
            PlatformUtil::openURL(PlatformUtil::getStoreUrl());
        }));
    
        container->addChild(createLinkWidget("icon_email.png", LocalizedString::getString("setting_email_us"), []() {
            PlatformUtil::presentEmailCompose("feedback@playflik.com", LocalizedString::getString("feedback_email_subject"),
                                              LocalizedString::getString("feedback_email_body"));
        }));
        
        // LOL MADE IN BROOKLYN
        auto madeInContainer = ui::VBox::create(Size(uiSize.width, 85.0_dp));
        madeInContainer->setPosition(Vec2(uiSize.width * 0.5, 25.0_dp));
        madeInContainer->setAnchorPoint(Vec2(0.5, 0.0));
        addChild(madeInContainer);
        
        auto label1 = Fonts::createLocalizedText(LocalizedString::getString("setting_made_in"), 15.0_dp);
        auto label1Layout = ui::LinearLayoutParameter::create();
        label1Layout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        label1->setLayoutParameter(label1Layout);
        madeInContainer->addChild(label1);
        
        auto label2 = Fonts::createLocalizedText("BROOKLYN", 25.0_dp);
        auto label2Layout = ui::LinearLayoutParameter::create();
        label2Layout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        label2Layout->setMargin(ui::Margin(0, 7.0_dp, 0, 0));
        label2->setLayoutParameter(label2Layout);
        madeInContainer->addChild(label2);
        
        auto label3 = Fonts::createLocalizedText("NYC", 15.0_dp);
        auto label3Layout = ui::LinearLayoutParameter::create();
        label3Layout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        label3Layout->setMargin(ui::Margin(0, 5.0_dp, 0, 0));
        label3->setLayoutParameter(label3Layout);
        madeInContainer->addChild(label3);
        
        return true;
    }
    
    void SettingsScene::onBackPressed()
    {
        SceneManager::popSceneWithTransition<TransitionSlideInL>(kTransitionDuration);
    }
}
