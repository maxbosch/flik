//
//  ChoosePowerupScene.cpp
//  Flik
//
//  Created by Adam Eskreis on 9/20/16.
//
//

#include "ChoosePowerupScene.h"
#include "Util.h"
#include "Literals.h"
#include "Styles.h"
#include "Fonts.h"
#include "LocalizedString.h"
#include "BonusBar.h"
#include "SceneManager.h"
#include "ChoosePowerupRowWidget.h"
#include "Player.h"
#include "ui/CocosGUI.h"
#include "StoreScene.h"
#include "Analytics.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace flik
{
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    ChoosePowerupScene* ChoosePowerupScene::create(const std::vector<BonusType>& currentBonuses, bool lockSelected)
    {
        return createWithParams<ChoosePowerupScene>(currentBonuses, lockSelected);
    }
    
    bool ChoosePowerupScene::init(const std::vector<BonusType>& currentBonuses, bool lockSelected)
    {
        if (!Scene::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        
        auto container = ui::VBox::create(uiSize);
        container->setBackGroundColor(Color3B::BLACK);
        container->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        addChild(container);
        
        auto exitButton = ui::Button::create("arrow_left.png");
        exitButton->setPosition(Vec2(20.0_dp, uiSize.height - 20.0_dp));
        exitButton->setAnchorPoint(Vec2(0.0, 1.0));
        addChild(exitButton);
        exitButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                onBackPressed();
            }
        });
        
        auto powerUpsLabel = Fonts::createLocalizedText(LocalizedString::getString("power_ups_title"), 23.0_dp);
        powerUpsLabel->setColor(kGoldColor);
        auto powerUpsLabelLayout = ui::LinearLayoutParameter::create();
        powerUpsLabelLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        powerUpsLabelLayout->setMargin(ui::Margin(0, 23.0_dp, 0, 0));
        powerUpsLabel->setLayoutParameter(powerUpsLabelLayout);
        container->addChild(powerUpsLabel);
        
        auto subtitle = Fonts::createLocalizedText(LocalizedString::getString("power_ups_choose_1"), 18.0_dp);
        subtitle->setColor(Color3B::WHITE);
        auto subtitleLayout = ui::LinearLayoutParameter::create();
        subtitleLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        subtitleLayout->setMargin(ui::Margin(0, 3.0_dp, 0,0));
        subtitle->setLayoutParameter(subtitleLayout);
        container->addChild(subtitle);
        
        auto bonusBar = BonusBar::create(Size(250.0_dp, 47.5_dp));
        bonusBar->setBonuses(currentBonuses);
        auto bonusBarLayout = ui::LinearLayoutParameter::create();
        bonusBarLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        bonusBarLayout->setMargin(ui::Margin(0, 15.0_dp, 0, 0));
        bonusBar->setLayoutParameter(bonusBarLayout);
        container->addChild(bonusBar);
        mBonusBar = bonusBar;
        mCurrentBonuses = currentBonuses;
        
        auto border = ui::HBox::create(Size(uiSize.width, 3.0_dp));
        border->setBackGroundColor(kBlueBorderColor);
        border->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        auto borderLayout = ui::LinearLayoutParameter::create();
        borderLayout->setMargin(ui::Margin(0, 30.0_dp, 0, 0));
        borderLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        border->setLayoutParameter(borderLayout);
        container->addChild(border);
        
        auto powerupsTable = ui::ScrollView::create();
        powerupsTable->setContentSize(Size(uiSize.width, uiSize.height - 175.0_dp));
        powerupsTable->setBounceEnabled(false);
        powerupsTable->setLayoutType(ui::Layout::Type::VERTICAL);
        powerupsTable->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
        powerupsTable->setScrollBarEnabled(true);
        powerupsTable->setScrollBarOpacity(255);
        powerupsTable->setScrollBarAutoHideEnabled(false);
        powerupsTable->setScrollBarWidth(9.0_dp);
        powerupsTable->setScrollBarColor(kMaroonColor);
        container->addChild(powerupsTable);
        mPowerupsTable = powerupsTable;
        
        if (lockSelected) {
            mLockedBonuses = currentBonuses;
        }
        refreshPowerupsTable();
        
        mCurrentBonuses = currentBonuses;
        
        return true;
    }
    
    void ChoosePowerupScene::onBackPressed()
    {
        SceneManager::popSceneWithTransition<TransitionSlideInL>(kTransitionDuration);
        
        PTree attributes;
        attributes.add("powerups", Util::bonusArrayString(mCurrentBonuses));
        Analytics::logEvent("choose_powerup_back", attributes);
    }
    
    void ChoosePowerupScene::onAppear()
    {
        SceneEx::onAppear();
        
        refreshPowerupsTable();
    }
    
    void ChoosePowerupScene::refreshPowerupsTable()
    {
        mPowerupsTable->removeAllChildren();
        
        auto buffer = ui::HBox::create(Size(getContentSize().width, 30.0_dp));
        mPowerupsTable->addChild(buffer);
        
        for (int i = 0; i < (int) BonusType::Count; i++) {
            auto cell = ChoosePowerupRowWidget::create();
            cell->setContentSize(Size(getContentSize().width, ChoosePowerupRowWidget::getCellHeight()));
                
            cell->onAddButtonTapped = [this](BonusType type, bool b) {
                auto child = dynamic_cast<ChoosePowerupRowWidget *>(mPowerupsTable->getChildren().at((int)type + 1));
                
                auto selected = std::find(mCurrentBonuses.begin(), mCurrentBonuses.end(), type);
                bool newSelected = false;
                
                if (selected == mCurrentBonuses.end()) {
                    if (mCurrentBonuses.size() < 3) {
                        mCurrentBonuses.push_back(type);
                        newSelected = true;
                    }
                } else {
                    mCurrentBonuses.erase(selected);
                }
                
                child->setData(type, newSelected);
                
                mBonusBar->setBonuses(mCurrentBonuses);
                
                if (onPowerupsChosen) {
                    onPowerupsChosen(mCurrentBonuses);
                    
                    Player::getMainPlayer()->setLastBonusChoices(mCurrentBonuses);
                }
                
                PTree attributes;
                attributes.add("powerup", kBonusStrings[type]);
                attributes.add("selected", (int)newSelected);
                attributes.add("quantity_remaining", Player::getMainPlayer()->getPowerUpCount(type));
                Analytics::logEvent("choose_powerup_add", attributes);
            };
            
            cell->onBuyButtonTapped = [this](BonusType type) {
                auto storeScene = StoreScene::create();
                SceneManager::pushSceneWithTransition<TransitionSlideInB>(storeScene, kTransitionDuration);
                
                PTree attributes;
                attributes.add("powerup", kBonusStrings[type]);
                Analytics::logEvent("choose_powerup_buy", attributes);
            };
            
            BonusType btype = static_cast<BonusType>(i);
            bool selected = std::find(mCurrentBonuses.begin(), mCurrentBonuses.end(), btype) != mCurrentBonuses.end();
            cell->setData(btype, selected);
            bool locked = std::find(mLockedBonuses.begin(), mLockedBonuses.end(), btype) != mLockedBonuses.end();
            cell->setLocked(locked);
            
            mPowerupsTable->addChild(cell);
        }
        
        mPowerupsTable->setInnerContainerSize(Size(mPowerupsTable->getContentSize().width,
                                                   (ChoosePowerupRowWidget::getCellHeight() * (int)BonusType::Count) + 30.0_dp));
        
        
    }
}
