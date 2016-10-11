//
//  StoreScene.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/9/16.
//
//

#include "StoreScene.h"
#include "StoreProductWidget.h"
#include "Styles.h"
#include "Literals.h"
#include "StorePurchaseOverlay.h"
#include "Player.h"
#include "SceneManager.h"
#include "Animations.h"
#include "LocalizedString.h"
#include "BuyPowerupRowWidget.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    bool StoreScene::init()
    {
        if (!Scene::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);
        
        auto storeGUI = ui::RelativeBox::create(uiSize);
        storeGUI->setPosition(Vec2(0, 0));
        storeGUI->setAnchorPoint(Vec2(0, 0));
        addChild(storeGUI);
        
        auto closeButton = ui::Button::create("arrow_down.png");
        closeButton->setRotation(180);
        auto closeButtonLayout = ui::RelativeLayoutParameter::create();
        closeButtonLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        closeButtonLayout->setMargin(ui::Margin(0, 20.0_dp, 0, 0));
        closeButtonLayout->setRelativeName("close_button");
        closeButton->setLayoutParameter(closeButtonLayout);
        storeGUI->addChild(closeButton);
        mCloseButton = closeButton;
        
        auto pointsButton = ui::Button::create("points_container.png");
        pointsButton->setTitleColor(Color3B::WHITE);
        pointsButton->setTitleFontName(Fonts::getFontForString("1234567890"));
        pointsButton->setTitleFontSize(25.0_dp);
        pointsButton->getTitleRenderer()->setAnchorPoint(Vec2(0, 0.5));
        pointsButton->getTitleRenderer()->setPosition(Vec2(12.0_dp, pointsButton->getContentSize().height * 0.5 - 2.0_dp));
        auto pointsButtonLayout = ui::RelativeLayoutParameter::create();
        pointsButtonLayout->setRelativeName("points_button");
        pointsButtonLayout->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
        pointsButtonLayout->setRelativeToWidgetName("close_button");
        pointsButtonLayout->setMargin(ui::Margin(0, 20.0_dp, 0, 20.0_dp));
        pointsButton->setLayoutParameter(pointsButtonLayout);
        storeGUI->addChild(pointsButton);
        mPointsButton = pointsButton;
        
        auto border1 = ui::HBox::create(Size(260.0_dp, 3.0_dp));
        border1->setBackGroundColor(kBlueBorderColor);
        border1->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        auto borderLayout1 = ui::RelativeLayoutParameter::create();
        borderLayout1->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
        borderLayout1->setMargin(ui::Margin(0, 30.0_dp, 0, 0));
        borderLayout1->setRelativeToWidgetName("points_button");
        borderLayout1->setRelativeName("border");
        border1->setLayoutParameter(borderLayout1);
        storeGUI->addChild(border1);
        
        auto productsContainer = ui::RelativeBox::create(Size(uiSize.width, 450.0_dp));
        auto productsContainerLayout = ui::RelativeLayoutParameter::create();
        productsContainerLayout->setRelativeToWidgetName("border");
        productsContainerLayout->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
        productsContainerLayout->setMargin(ui::Margin(0, 30.0_dp, 0, 0));
        productsContainer->setLayoutParameter(productsContainerLayout);
        storeGUI->addChild(productsContainer);
        mProductsContainer = productsContainer;
        
        auto productsTable = TableView::create(this, productsContainer->getContentSize());
        productsContainer->addChild(productsTable);
        productsTable->reloadData();
        
        closeButton->addTouchEventListener([this](Ref* sender, StoreProductWidget::TouchEventType type) {
            if (type == StoreProductWidget::TouchEventType::ENDED) {
                onBackPressed();
            }
        });
        
        auto storePurchaseOverlay = StorePurchaseOverlay::create();
        auto storePurchaseOverlayLayout = ui::RelativeLayoutParameter::create();
        storePurchaseOverlayLayout->setAlign(RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
        storePurchaseOverlayLayout->setMargin(ui::Margin(0, 0, 0, 35.0_dp));
        storePurchaseOverlay->setLayoutParameter(storePurchaseOverlayLayout);
        storeGUI->addChild(storePurchaseOverlay);
        mPurchaseOverlay = storePurchaseOverlay;
        setPurchaseOverlayVisible(false, false);
        
        pointsButton->addTouchEventListener([this](Ref* sender, StoreProductWidget::TouchEventType type) {
            if (type == StoreProductWidget::TouchEventType::ENDED) {
                setPurchaseOverlayVisible(true);
            }
        });
        
        this->scheduleUpdate();
        
        return true;
    }
    
    void StoreScene::update(float seconds)
    {
        Scene::update(seconds);
        
        mPointsButton->getTitleRenderer()->setString(boost::lexical_cast<std::string>(Player::getMainPlayer()->getCurrencyAmount()));
    }
    
    void StoreScene::setPurchaseOverlayVisible(bool visible, bool animated)
    {
        if (animated) {
            if (visible) {
                mPurchaseOverlay->setVisible(true);
                mPurchaseOverlay->setScale(0);
                Animations::animate(kTransitionDuration, [this](float t) {
                    mPurchaseOverlay->setScale(t);
                }, nullptr, OvershootCurve);
            } else {
                mPurchaseOverlay->setScale(1);
                Animations::animate(0.2, [this](float t) {
                    mPurchaseOverlay->setScale(1.0 - t);
                }, [this](bool finished) {
                    mPurchaseOverlay->setVisible(false);
                });
            }
        } else {
            mPurchaseOverlay->setVisible(visible);
        }
        
        if (visible) {
            mCloseButton->loadTextureNormal("red_x_close.png");
        } else {
            mCloseButton->loadTextureNormal("arrow_down.png");
        }
    }
    
    void StoreScene::onProductPurchaseRequested(PowerUpType type, int cost, int quantity)
    {
        auto player = Player::getMainPlayer();
        if (player->getCurrencyAmount() >= cost) {
            player->removeCurrency(cost);
            //player->addPowerUp(type, quantity);
        } else {
            setPurchaseOverlayVisible(true);
        }
    }
    
    void StoreScene::onBackPressed()
    {
        if (mPurchaseOverlay->isVisible()) {
            setPurchaseOverlayVisible(false);
        } else {
            SceneManager::popSceneWithTransition<TransitionSlideInT>(kTransitionDuration);
        }
    }
    
    /* TableViewDataSource */
    /* TableViewDataSource methods */
    Size StoreScene::cellSizeForTable(TableView *table)
    {
        return Size(getContentSize().width, ChoosePowerupRowWidget::getCellHeight());
    }
    
    TableViewCell* StoreScene::tableCellAtIndex(TableView *table, ssize_t idx)
    {
        auto cell = dynamic_cast<BuyPowerupRowWidget*>(table->dequeueCell());
        if (cell == nullptr) {
            cell = BuyPowerupRowWidget::create();
            cell->onBuyItemRequested = [this, table](BonusType type, int cost) {
                auto player = Player::getMainPlayer();
                if (player->getCurrencyAmount() >= cost) {
                    player->removeCurrency(cost);
                    player->addPowerUp(type, 1);
                    
                    int idx = (static_cast<int>(BonusType::Count) - 1) - static_cast<int>(type);
                    table->updateCellAtIndex(idx);
                } else {
                    setPurchaseOverlayVisible(true);
                }
            };
        }
        
        BonusType btype = static_cast<BonusType>((static_cast<int>(BonusType::Count) - 1) - idx);
        cell->setData(btype, false);
        
        return cell;
    }
    
    ssize_t StoreScene::numberOfCellsInTableView(TableView *table)
    {
        return (ssize_t) BonusType::Count;
    }
}
