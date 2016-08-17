//
//  LevelObjectiveOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/16/16.
//
//

#include <boost/algorithm/string/case_conv.hpp>

#include "LevelObjectiveOverlay.h"
#include "Util.h"
#include "LevelTypes.h"
#include "Fonts.h"
#include "Styles.h"
#include "LocalizedString.h"
#include "Literals.h"
#include "format.h"

using namespace fmt::literals;

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    LevelObjectiveOverlay* LevelObjectiveOverlay::create(const std::string& title, const LevelDescription* levelDesc, int sublevel)
    {
        return createWithParams<LevelObjectiveOverlay>(title, levelDesc, sublevel);
    }
    
    bool LevelObjectiveOverlay::init(const std::string& title, const LevelDescription* levelDesc, int sublevel)
    {
        mLevelDesc = levelDesc;
        mSublevel = sublevel;
        
        return GameObjectiveOverlay::init(title);
    }
    
    ui::Widget* LevelObjectiveOverlay::createTitleWidget(const std::string& title)
    {
        auto titleContainer = ui::RelativeBox::create(Size(getContentSize().width, 110.0_dp));
        auto titleContainerLayout = ui::LinearLayoutParameter::create();
        titleContainerLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        titleContainer->setLayoutParameter(titleContainerLayout);
        
        auto titleLabel = Fonts::createLocalizedText(title, 25.0_dp);
        titleLabel->setColor(kGoldColor);
        auto titleLabelLayout = ui::RelativeLayoutParameter::create();
        titleLabelLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        titleLabelLayout->setRelativeName("title");
        titleLabelLayout->setMargin(ui::Margin(0, 30.0_dp, 0, 0));
        titleLabel->setLayoutParameter(titleLabelLayout);
        titleContainer->addChild(titleLabel);
        
        auto subtitleLabel = Fonts::createLocalizedText(boost::to_upper_copy(LocalizedString::getString("game_mode_level", mSublevel + 1)), 18.0_dp);
        subtitleLabel->setColor(Color3B::WHITE);
        auto subtitleLabelLayout = ui::RelativeLayoutParameter::create();
        subtitleLabelLayout->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
        subtitleLabelLayout->setMargin(ui::Margin(0, 5.0_dp, 0, 0));
        subtitleLabelLayout->setRelativeToWidgetName("title");
        subtitleLabel->setLayoutParameter(subtitleLabelLayout);
        titleContainer->addChild(subtitleLabel);
        
        return titleContainer;
    }
    
    ui::Widget* LevelObjectiveOverlay::createObjectiveWidget()
    {
        auto& level = mLevelDesc->data["sublevels"][mSublevel];
        auto& objectives = level["objectives"];
        auto& objective = objectives[0];
        
        std::string name = mLevelDesc->data["name"].GetString();
        std::string text = LocalizedString::getString("objective_game_" + name);
        
        auto widget = Fonts::createLocalizedText(fmt::format(text,
                                                             "quantity"_a=objective["quantity"].GetInt(),
                                                             "time_limit"_a=level["time_limit"].GetInt()), 18.0_dp);
        //widget->setColor(kGoldColor);
        widget->setTextAreaSize(Size(250.0_dp, 80.0_dp));
        widget->setTextHorizontalAlignment(TextHAlignment::CENTER);
        return widget;
    }
}