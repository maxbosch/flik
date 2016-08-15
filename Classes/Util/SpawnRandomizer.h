//
//  SpawnRandomizer.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/20/16.
//
//

#include <queue>

#pragma once

namespace flik
{
    class SpawnRandomizer
    {
    public:
        static SpawnRandomizer* getInstance();
        
        void reset();
        int getRandomId();
        
        void setNumPieces(int num);
        
    private:
        SpawnRandomizer() {};
        
        void reshuffle();
        
        int mNumPieces;
        std::queue<int> mRandomQueue;
    };
}
