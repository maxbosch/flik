//
//  Player.hpp
//  Fling
//
//  Created by Adam Eskreis on 5/31/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    class Player
    {
    public:
        static Player* getMainPlayer();
        
        int getTopScore(std::string key);
        
        void resetScore();
        void addScore(int amount);
        int getCurrentScore() { return mCurrentScore; }
        void recordScore(std::string key);
        
    private:
        Player();
        
        int mCurrentScore;
    };
}
