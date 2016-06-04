//
//  VelocityTracker.hpp
//  Fling
//
//  Created by Adam Eskreis on 5/25/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
    
    struct VelocityTrackerPoint
    {
        TimePoint time;
        cocos2d::Vec2 point;
    };
    
    class VelocityTracker
    {
    public:
        VelocityTracker();
        
        void Reset();
        void AddPoint(cocos2d::Vec2 point);
        
        cocos2d::Vec2 GetVelocity() { return mCurrentVelocity; }
        
    private:
        std::vector<VelocityTrackerPoint> mPoints;
        cocos2d::Vec2 mCurrentVelocity;
    };
}
