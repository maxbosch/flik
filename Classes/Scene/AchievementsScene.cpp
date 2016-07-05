//
//  AchievementsScene.cpp
//  Flik
//
//  Created by Adam Eskreis on 7/5/16.
//
//

#include "AchievementsScene.h"
#include "Styles.h"
#include "Literals.h"
#include "SceneManager.h"
#include "Player.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    bool AchievementsScene::init()
    {
        if (!Scene::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);
        
        auto container = ui::VBox::create(uiSize);
        container->setBackGroundColor(kBlueColor);
        container->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        container->setPosition(Vec2());
        container->setAnchorPoint(Vec2());
        container->setContentSize(uiSize);
        addChild(container);
        
        // Header
        
        auto header = ui::RelativeBox::create(Size(uiSize.width, 82.5_dp));
        container->addChild(header);
        
        auto title = ui::Text::create("ACHIEVEMENTS", kDefaultFont, 25.0_dp);
        title->setTextVerticalAlignment(cocos2d::TextVAlignment::CENTER);
        auto titleLayout = ui::RelativeLayoutParameter::create();
        titleLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        titleLayout->setMargin(ui::Margin(0, 29.0_dp, 0, 0));
        title->setLayoutParameter(titleLayout);
        header->addChild(title);
        
        auto backButton = ui::Button::create("arrow_right.png");
        auto backButtonLayout = ui::RelativeLayoutParameter::create();
        backButtonLayout->setAlign(RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
        backButtonLayout->setMargin(ui::Margin(0, 0, 20.0_dp, 0));
        backButton->setLayoutParameter(backButtonLayout);
        header->addChild(backButton);
        
        backButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                SceneManager::popSceneWithTransition<TransitionSlideInR>(kTransitionDuration);
            }
        });
        
        auto makeBorder = [uiSize]() {
            auto borderColor = Util::getColorFromHex("004380");
            
            auto border = ui::HBox::create(Size(uiSize.width, 0.5_dp));
            border->setBackGroundColor(borderColor);
            border->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
            
            return border;
        };
        
        container->addChild(makeBorder());
        
        // Top scores
        auto topScoreContainer = ui::HBox::create(Size(uiSize.width, 120.0_dp));
        container->addChild(topScoreContainer);
        
        auto createTopScoreWidget = [uiSize](const std::string& name, int value, float ratio) {
            auto container = ui::RelativeBox::create(Size(uiSize.width * ratio, 120.0_dp));
            
            auto label = ui::Text::create("Best " + name, kDefaultFont, 15.0_dp);
            auto labelLayout = ui::RelativeLayoutParameter::create();
            labelLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
            labelLayout->setMargin(ui::Margin(0, 35.0_dp, 0, 0));
            labelLayout->setRelativeName("label");
            label->setLayoutParameter(labelLayout);
            container->addChild(label);
            
            auto valueLabel = ui::Text::create(boost::lexical_cast<std::string>(value), kDefaultFont, 25.0_dp);
            auto valueLabelLayout = ui::RelativeLayoutParameter::create();
            valueLabelLayout->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
            valueLabelLayout->setMargin(ui::Margin(0, 3.0_dp, 0, 0));
            valueLabelLayout->setRelativeToWidgetName("label");
            valueLabel->setLayoutParameter(valueLabelLayout);
            container->addChild(valueLabel);
            
            return container;
        };
        
        int numScores = 2;
        float ratio = 1.0 / (float)numScores;
        topScoreContainer->addChild(createTopScoreWidget("Timed", Player::getMainPlayer()->getTopScore("timed"), ratio));
        topScoreContainer->addChild(createTopScoreWidget("Unlimited", Player::getMainPlayer()->getTopScore("unlimited"), ratio));
        
        container->addChild(makeBorder());
        
        // List View
        int scrollViewHeight = uiSize.height - topScoreContainer->getContentSize().height - header->getContentSize().height - 1;
        
        auto achievementsTable = ui::TableView::create(this, Size(uiSize.width, scrollViewHeight));
        return true;
    }
    
    /* TableViewDataSource methods */
    Size AchievementsScene::cellSizeForTable(TableView *table)
    {
        
    }
    
    TableViewCell* AchievementsScene::tableCellAtIndex(TableView *table, ssize_t idx)
    {
        
    }
    
    ssize_t AchievementsScene::numberOfCellsInTableView(TableView *table)
    {
        
    }
}