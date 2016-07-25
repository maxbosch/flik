//
//  TextObjectiveOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/15/16.
//
//

#include "TextObjectiveOverlay.h"
#include "Util.h"
#include "Styles.h"
#include "Literals.h"

USING_NS_CC;

namespace flik
{
    TextObjectiveOverlay* TextObjectiveOverlay::create(const std::string& title, const std::string& text)
    {
        return createWithParams<TextObjectiveOverlay>(title, text);
    }
    
    bool TextObjectiveOverlay::init(const std::string& title, const std::string& text)
    {
        mText = text;
        
        return GameObjectiveOverlay::init(title);
    }
    
    ui::Widget* TextObjectiveOverlay::createObjectiveWidget()
    {
        auto textWidget = Fonts::createLocalizedText(mText, 15.0_dp);
        textWidget->setColor(Color3B::WHITE);
        textWidget->setTextHorizontalAlignment(TextHAlignment::CENTER);
        textWidget->setTextAreaSize(Size(250.0_dp, 80.0_dp));
        return textWidget;
    }
}
