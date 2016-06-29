//
//  SpawnRandomizer.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/20/16.
//
//


#include "SpawnRandomizer.h"
#include "cocos2d.h"

namespace flik
{
    static SpawnRandomizer* sInstance = NULL;
    
    static const int kBufferSize = 5;
    static const int kIterations = 50;
    
    SpawnRandomizer* SpawnRandomizer::getInstance()
    {
        if (!sInstance) {
            sInstance = new SpawnRandomizer();
            sInstance->setNumPieces(4);
        }
        
        return sInstance;
    }
    
    void SpawnRandomizer::reset()
    {
        while (!mRandomQueue.empty()) {
            mRandomQueue.pop();
        }
        
        reshuffle();
    }
    
    int SpawnRandomizer::getRandomId()
    {
        if (mRandomQueue.empty()) {
            reshuffle();
        }
        
        int next = mRandomQueue.front();
        mRandomQueue.pop();
        
        return next;
    }
    
    void SpawnRandomizer::setNumPieces(int num)
    {
        mNumPieces = num;
        
        reset();
    }
    
    void SpawnRandomizer::reshuffle()
    {
        std::vector<int> items;
        for (int i = 0; i < kBufferSize; i++) {
            for (int j = 0; j < mNumPieces; j++) {
                items.push_back(j);
            }
        }
        
        for (int i = 0; i < kIterations; i++) {
            int random1 = cocos2d::random<int>(0, (int) items.size() - 1);
            int random2 = cocos2d::random<int>(0, (int) items.size() - 1);
            
            std::swap(items[random1], items[random2]);
        }
        
        for (int id : items) {
            mRandomQueue.push(id);
        }
    }
}