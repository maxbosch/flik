//
//  ChoosePowerupRowWidget.hpp
//  Flik
//
//  Created by Adam Eskreis on 9/21/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GUI/CCScrollView/CCTableView.h"
#include "Enums.h"

namespace flik
{
    class ChoosePowerupRowWidget : public cocos2d::extension::TableViewCell
    {
    public:
        CREATE_FUNC(ChoosePowerupRowWidget);
        
        bool init();
        
        virtual void setData(BonusType type, bool selected);
        void setLocked();
        
        static float getCellHeight();
        
        std::function<void(BonusType, bool)> onAddButtonTapped;
        std::function<void()> onBuyButtonTapped;
        
    protected:
        cocos2d::ui::Button* getAddButton() { return mAddButton; }
        
    private:
        cocos2d::ui::ImageView* mImage;
        cocos2d::ui::Button* mAddButton;
        cocos2d::ui::Text* mNameLabel;
        cocos2d::ui::Text* mDescriptionLabel;
        cocos2d::ui::Text* mCountLabel;
        
        BonusType mBonusType;
        bool mSelected;
        int mCount;
    };
}
