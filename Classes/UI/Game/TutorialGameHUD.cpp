//
//  TutorialGameHUD.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/29/16.
//
//

#include "TutorialGameHUD.h"
#include "GameBoard.h"
#include "Styles.h"
#include "Literals.h"
#include "TutorialGameMode.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include "MainGameScene.h"
#include "ValueAnimation.h"

USING_NS_CC;

namespace flik
{
    struct TutorialTextInterpolator : public Interpolator
    {
        float factor = 0.25;
        float multiplier = 1.0f / factor;
        
        float operator()(float t)
        {
            if (t < factor) {
                return t * multiplier;
            } else if (t > (1.0 - factor)) {
                return ((1.0f - t) * multiplier);
            }
            
            return 1.0f;
        }
    };
    
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    bool TutorialGameHUD::init()
    {
        if (!GameHUD::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);
        
        setBackGroundColor(Color3B::BLACK);
        setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        
        auto header = ui::RelativeBox::create(Size(uiSize.width, 70.0_dp));
        header->setBackGroundColor(Color3B::BLACK);
        header->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        auto headerLayout = ui::RelativeLayoutParameter::create();
        headerLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        header->setLayoutParameter(headerLayout);
        addChild(header, 2);
        
        auto headerImage = ui::ImageView::create("flik_small.png");
        auto headerImageLayout = ui::RelativeLayoutParameter::create();
        headerImageLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        headerImageLayout->setMargin(ui::Margin(0, 10.0_dp, 0, 0));
        headerImage->setLayoutParameter(headerImageLayout);
        header->addChild(headerImage);
        
        auto gameBoard = GameBoard::create();
        gameBoard->setBackGroundColor(Color3B::BLACK);
        gameBoard->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        gameBoard->setContentSize(Size(uiSize.width, uiSize.height - 70.0_dp));
        auto gameBoardLayout = ui::RelativeLayoutParameter::create();
        gameBoardLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        gameBoardLayout->setMargin(ui::Margin(0, 70.0_dp, 0, 0));
        gameBoard->setLayoutParameter(gameBoardLayout);
        addChild(gameBoard, 1);
        mGameBoard = gameBoard;
        
        auto tutorialText = ui::Text::create("", kDefaultFont, 20.0_dp);
        tutorialText->setTextHorizontalAlignment(TextHAlignment::CENTER);
        auto tutorialTextLayout = ui::RelativeLayoutParameter::create();
        tutorialTextLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        tutorialTextLayout->setMargin(ui::Margin(0, 160.0_dp, 0, 0));
        tutorialText->setLayoutParameter(tutorialTextLayout);
        mGameBoard->addChild(tutorialText, 2);
        mTutorialText = tutorialText;
        
        float margin = 60.0_dp;
        
        auto arrow = ui::ImageView::create("tutorial_arrow.png");
        auto arrowLayout = ui::RelativeLayoutParameter::create();
        arrowLayout->setMargin(ui::Margin(margin, margin, margin, margin));
        arrowLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        arrow->setLayoutParameter(arrowLayout);
        mGameBoard->addChild(arrow, 2);
        arrow->setVisible(false);
        
        mArrow = arrow;
        mArrowLayout = arrowLayout;
        
        
        executeTutorialIntroAnimation();
        
        return true;
    }
    
    void TutorialGameHUD::setArrowPosition(TutorialArrowPosition position, float rotation)
    {
        mArrow->setRotation(rotation);
 
        switch (position) {
            case TutorialArrowPosition::TopLeft:
                mArrowLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
                break;
                
            case TutorialArrowPosition::TopRight:
                mArrowLayout->setAlign(RelativeAlign::PARENT_TOP_RIGHT);
                break;
                
            case TutorialArrowPosition::BottomLeft:
                mArrowLayout->setAlign(RelativeAlign::PARENT_LEFT_BOTTOM);
                break;
                
            case TutorialArrowPosition::BottomRight:
                mArrowLayout->setAlign(RelativeAlign::PARENT_RIGHT_BOTTOM);
                break;
                
            default:
                break;
        }

        forceDoLayout();
    }
    
    void TutorialGameHUD::onGameStateChanged(GameState newState)
    {
        GameHUD::onGameStateChanged(newState);
        
        if (newState == GameState::Finished) {
            mArrow->setVisible(false);
            executeTutorialExitAnimation();
        }
    }
    
    void TutorialGameHUD::update(float t)
    {
        if (mTextAnimation) {
            if (mTextAnimation->IsFinished()) {
                mTextAnimation = nullptr;
            } else {
                mTextAnimation->Update(t);
            }
        }
    }
    
    void TutorialGameHUD::executeTutorialIntroAnimation()
    {
        mTutorialText->setString("Welcome to Flik!\nHow about a quick tutorial first?");
        mTutorialText->setOpacity(0);
        
        mTextAnimation = std::shared_ptr<ValueAnimationf>(new ValueAnimationf(0, 255, [this](const ValueAnimationf* animator, const float t) {
            mTutorialText->setOpacity(t);
        }));
        mTextAnimation->SetCompletion([this](Animation* completed) {
            mTutorialText->setString("Move the piece to\n its matching color");
            mTutorialText->setOpacity(255);
            mArrow->setVisible(true);
            getGameScene()->requestRestart();
        });
        mTextAnimation->SetDuration(3.0);
        mTextAnimation->SetInterpolationFunction(std::unique_ptr<TutorialTextInterpolator>(new TutorialTextInterpolator()));
        mTextAnimation->Start();
    }
    
    void TutorialGameHUD::executeTutorialExitAnimation()
    {
        mTutorialText->setString("Awesome!\n Now for a real challenge...");
        mTutorialText->setOpacity(0);
        
        mTextAnimation = std::shared_ptr<ValueAnimationf>(new ValueAnimationf(0, 255, [this](const ValueAnimationf* animator, const float t) {
            mTutorialText->setOpacity(t);
        }));
        mTextAnimation->SetCompletion([this](Animation* completed) {
            SceneManager::replaceSceneWithTransition<TransitionSlideInR>(MainMenuScene::create(), kTransitionDuration);
        });
        mTextAnimation->SetDuration(3.0);
        mTextAnimation->SetInterpolationFunction(std::unique_ptr<TutorialTextInterpolator>(new TutorialTextInterpolator()));
        mTextAnimation->Start();
    }
}