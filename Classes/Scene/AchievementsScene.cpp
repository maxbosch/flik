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
#include "LocalizedString.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    static auto makeBorder = []() {
        auto uiSize = Director::getInstance()->getVisibleSize();
        
        auto borderColor = Util::getColorFromHex("004380");
        
        auto border = ui::HBox::create(Size(uiSize.width, 0.5_dp));
        border->setBackGroundColor(borderColor);
        border->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        
        return border;
    };
    
    class AchievementTableCell : public TableViewCell
    {
    public:
        CREATE_FUNC(AchievementTableCell);
        
        static double getCellHeight() { return 81.5_dp; }
        
        bool init()
        {
            if (!TableViewCell::init())
            {
                return false;
            }
            
            auto uiSize = Director::getInstance()->getVisibleSize();
            
            auto container = ui::RelativeBox::create(Size(uiSize.width, getCellHeight()));
            container->setPosition(Vec2(0, 0));
            container->setAnchorPoint(Vec2(0, 0));
            addChild(container);
            
            auto nameText = ui::Text::create("Play a game in Timed Mode", kDefaultFont, 18.0_dp);
            nameText->setTextAreaSize(Size(200.0_dp, 40.0_dp));
            nameText->setTextVerticalAlignment(TextVAlignment::CENTER);
            auto nameTextLayout = ui::RelativeLayoutParameter::create();
            nameTextLayout->setAlign(RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
            nameTextLayout->setMargin(ui::Margin(40.0_dp, 0, 0, 0));
            nameText->setLayoutParameter(nameTextLayout);
            container->addChild(nameText);
            
            auto imageView = ui::ImageView::create("achievement_incomplete.png");
            auto imageViewLayout = ui::RelativeLayoutParameter::create();
            imageViewLayout->setAlign(RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
            imageViewLayout->setMargin(ui::Margin(0, 0, 40.0_dp, 0));
            imageView->setLayoutParameter(imageViewLayout);
            container->addChild(imageView);
            mCompletionImage = imageView;
            
            auto border = makeBorder();
            auto borderLayout = ui::RelativeLayoutParameter::create();
            borderLayout->setAlign(RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
            border->setLayoutParameter(borderLayout);
            container->addChild(border);
            
            return true;
        }
        
        void setAchievement(ssize_t uIdx)
        {
            bool complete = uIdx % 2 == 0;
            
            printf("Complete: %d", complete);
            if (complete) {
                mCompletionImage->loadTexture("achievement_complete.png");
            } else {
                mCompletionImage->loadTexture("achievement_incomplete.png");
            }
        }
        
        ui::ImageView* mCompletionImage;
    };
    
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
        
        auto title = ui::Text::create(LocalizedString::getString("title_achievements"), kDefaultFont, 25.0_dp);
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
        
        container->addChild(makeBorder());
        
        // Top scores
        auto topScoreContainer = ui::HBox::create(Size(uiSize.width, 120.0_dp));
        container->addChild(topScoreContainer);
        
        auto createTopScoreWidget = [uiSize](const std::string& name, int value, float ratio) {
            auto container = ui::RelativeBox::create(Size(uiSize.width * ratio, 120.0_dp));
            
            auto label = ui::Text::create(name, kDefaultFont, 15.0_dp);
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
        topScoreContainer->addChild(createTopScoreWidget(LocalizedString::getString("achievements_best_timed"),
                                                         Player::getMainPlayer()->getTopScore("timed"), ratio));
        topScoreContainer->addChild(createTopScoreWidget(LocalizedString::getString("achievements_best_unlimited"),
                                                         Player::getMainPlayer()->getTopScore("unlimited"), ratio));
        
        container->addChild(makeBorder());
        
        // List View
        int scrollViewHeight = uiSize.height - topScoreContainer->getContentSize().height - header->getContentSize().height - 1;
        
        auto achievementsTable = TableView::create(this, Size(uiSize.width, scrollViewHeight));
        addChild(achievementsTable);
        
        return true;
    }
    
    /* TableViewDataSource methods */
    Size AchievementsScene::cellSizeForTable(TableView *table)
    {
        return Size(getContentSize().width, AchievementTableCell::getCellHeight());
    }
    
    TableViewCell* AchievementsScene::tableCellAtIndex(TableView *table, ssize_t idx)
    {
        auto cell = dynamic_cast<AchievementTableCell*>(table->dequeueCell());
        if (cell == nullptr) {
            cell = AchievementTableCell::create();
        }
        
        cell->setAchievement(idx);
        
        return cell;
    }
    
    ssize_t AchievementsScene::numberOfCellsInTableView(TableView *table)
    {
        return 10;
    }
}