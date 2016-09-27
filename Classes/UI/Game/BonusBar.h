//
//  BonusBar.hpp
//  Flik
//
//  Created by Adam Eskreis on 9/12/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Enums.h"

namespace flik
{
    class BonusBar : public cocos2d::ui::HBox
    {
    public:
        static BonusBar* create(const cocos2d::Size& size);
        
        bool init(const cocos2d::Size& size);
    
        void setBonuses(const std::vector<BonusType>& bonuses);
        void reset();
        
        std::function<void(BonusType)> onBonusTapped;
        std::function<void()> onAddBonusTapped;
        
        void disableBonus(int bonus);
        const std::vector<BonusType>& getBonuses() { return mBonuses; }
        
    private:
        std::vector<cocos2d::ui::Button*> mButtons;
        std::vector<BonusType> mBonuses;
    };
}
