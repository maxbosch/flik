//
//  ScoreWidget.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/18/16.
//
//

#include <boost/lexical_cast.hpp>

#include "ScoreWidget.h"
#include "Util.h"
#include "Styles.h"
#include "Literals.h"

USING_NS_CC;

namespace flik
{
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    ScoreWidget* ScoreWidget::create(const std::string& title)
    {
        return createWithParams<ScoreWidget>(title);
    }
    
    bool ScoreWidget::init(const std::string& title)
    {
        if (!VBox::init())
        {
            return false;
        }
        
        auto titleLabel = ui::Text::create(title, kDefaultFont, 18.0_dp);
        titleLabel->setColor(Color3B::WHITE);
        auto titleLabelLayout = ui::LinearLayoutParameter::create();
        titleLabelLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        titleLabelLayout->setMargin(ui::Margin(0, 0, 0, 5.0_dp));
        titleLabel->setLayoutParameter(titleLabelLayout);
        addChild(titleLabel);
        
        auto scoreLabel = ui::Text::create("0", kDefaultFont, 25.0_dp);
        scoreLabel->setColor(Color3B::WHITE);
        auto scoreLabelLayout = ui::LinearLayoutParameter::create();
        scoreLabelLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        scoreLabel->setLayoutParameter(scoreLabelLayout);
        addChild(scoreLabel);
        mScoreLabel = scoreLabel;
        
        setContentSize(getLayoutAccumulatedSize());
        
        return true;
    }
    
    void ScoreWidget::setScore(int score)
    {
        mScoreLabel->setString(boost::lexical_cast<std::string>(score));
    }
}
