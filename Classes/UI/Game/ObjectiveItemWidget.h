//
//  ObjectiveItemWidget.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/16/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class ObjectiveItemWidget : public cocos2d::ui::RelativeBox
    {
    public:
        static ObjectiveItemWidget* create(const std::string& normalImage, const std::string& completedImage, int quantity);
        
        bool init(const std::string& normalImage, const std::string& completedImage, int quantity);
        
        bool isComplete() { return mCompleted; }
        
        void incrementObjective(int count);
        
        void update(float time);
        
    private:
        cocos2d::ui::ImageView* mImage;
        cocos2d::ui::Text* mText;
        
        std::string mCompletedImage;
        int mQuantity;
        int mCurrentCount;
        bool mCompleted;
    };
}
