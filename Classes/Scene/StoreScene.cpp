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

USING_NS_CC;

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
        
        auto pointsButton = ui::Button::create("points_container.png");
        pointsButton->setTitleColor(Color3B::WHITE);
        pointsButton->setTitleFontName(Fonts::getFontForString("1234567890"));
        pointsButton->setTitleFontSize(25.0_dp);
        pointsButton->getTitleRenderer()->setAnchorPoint(Vec2(0, 0.5));
        pointsButton->getTitleRenderer()->setPosition(Vec2(12.0_dp, pointsButton->getContentSize().height * 0.5 - 2.0_dp));
        auto pointsButtonLayout = ui::RelativeLayoutParameter::create();
        pointsButtonLayout->setRelativeName("points_button");
        pointsButtonLayout->setAlign(RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
        pointsButtonLayout->setMargin(ui::Margin(0, 0, 0, 20.0_dp));
        pointsButton->setLayoutParameter(pointsButtonLayout);
        storeGUI->addChild(pointsButton);
        mPointsButton = pointsButton;
        
        auto productsCopy = Fonts::createLocalizedText(LocalizedString::getString("store_power_ups"), 25.0_dp);
        productsCopy->setColor(Color3B::WHITE);
        auto productsCopyLayout = ui::RelativeLayoutParameter::create();
        productsCopyLayout->setRelativeToWidgetName("close_button");
        productsCopyLayout->setRelativeName("products_copy");
        productsCopyLayout->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
        productsCopyLayout->setMargin(ui::Margin(0, 90.0_dp, 0, 0));
        productsCopy->setLayoutParameter(productsCopyLayout);
        storeGUI->addChild(productsCopy);
        
        auto productsContainer = ui::RelativeBox::create(Size(uiSize.width, 200.0_dp));
        auto productsContainerLayout = ui::RelativeLayoutParameter::create();
        productsContainerLayout->setRelativeToWidgetName("products_copy");
        productsContainerLayout->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
        productsContainerLayout->setMargin(ui::Margin(0, 50.0_dp, 0, 0));
        productsContainer->setLayoutParameter(productsContainerLayout);
        storeGUI->addChild(productsContainer);
        mProductsContainer = productsContainer;
        
        auto timeStopProduct = StoreProductWidget::create(PowerUpType::Timestop, 1000, 5, LocalizedString::getString("store_product_time_stops"));
        auto timeStopsProductLayout = ui::RelativeLayoutParameter::create();
        timeStopsProductLayout->setAlign(RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
        timeStopsProductLayout->setMargin(ui::Margin(40.0_dp, 0, 0, 0));
        timeStopProduct->setLayoutParameter(timeStopsProductLayout);
        productsContainer->addChild(timeStopProduct);
        
        auto targetProduct = StoreProductWidget::create(PowerUpType::Target, 500, 5, LocalizedString::getString("store_product_board_clears"));
        auto targetProductLayout = ui::RelativeLayoutParameter::create();
        targetProductLayout->setAlign(RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
        targetProductLayout->setMargin(ui::Margin(0, 0, 40.0_dp, 0));
        targetProduct->setLayoutParameter(targetProductLayout);
        productsContainer->addChild(targetProduct);
        
        auto closeButton = ui::Button::create("arrow_down.png");
        closeButton->setRotation(180);
        auto closeButtonLayout = ui::RelativeLayoutParameter::create();
        closeButtonLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        closeButtonLayout->setRelativeName("close_button");
        closeButtonLayout->setMargin(ui::Margin(0, 20.0_dp, 0, 0));
        closeButton->setLayoutParameter(closeButtonLayout);
        storeGUI->addChild(closeButton);
        mCloseButton = closeButton;
        
        closeButton->addTouchEventListener([this](Ref* sender, StoreProductWidget::TouchEventType type) {
            if (type == StoreProductWidget::TouchEventType::ENDED) {
                if (mPurchaseOverlay->isVisible()) {
                    setPurchaseOverlayVisible(false);
                } else {
                    SceneManager::popSceneWithTransition<TransitionSlideInT>(kTransitionDuration);
                }
            }
        });
        
        auto storePurchaseOverlay = StorePurchaseOverlay::create();
        auto storePurchaseOverlayLayout = ui::RelativeLayoutParameter::create();
        storePurchaseOverlayLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        //storePurchaseOverlayLayout->setMargin(ui::Margin(0, 0, 0, 0));
        storePurchaseOverlay->setLayoutParameter(storePurchaseOverlayLayout);
        storeGUI->addChild(storePurchaseOverlay);
        mPurchaseOverlay = storePurchaseOverlay;
        setPurchaseOverlayVisible(false, false);
        
        timeStopProduct->onProductPurchaseRequested = CC_CALLBACK_3(StoreScene::onProductPurchaseRequested, this);
        targetProduct->onProductPurchaseRequested = CC_CALLBACK_3(StoreScene::onProductPurchaseRequested, this);
        
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
            player->addPowerUp(type, quantity);
        } else {
            setPurchaseOverlayVisible(true);
        }
    }
}