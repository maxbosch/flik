//
//  MainGameHeader.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/8/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class MainGameHeader : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(MainGameHeader);
        
        bool init();
        
        void setScore(int score);
        
    private:
        cocos2d::ui::Text* mScoreLabel;
    };
    
}


