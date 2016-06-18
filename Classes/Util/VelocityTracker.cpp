//
//  VelocityTracker.cpp
//  Fling
//
//  Created by Adam Eskreis on 5/25/16.
//
//

#include "VelocityTracker.h"

USING_NS_CC;

namespace flik
{
    static const int kMaxPoints = 20;
    
    VelocityTracker::VelocityTracker()
    {
    }
    
    void VelocityTracker::Reset()
    {
        mPoints.clear();
        mCurrentVelocity = Vec2();
    }
    
    void VelocityTracker::AddPoint(cocos2d::Vec2 point)
    {
        mPoints.push_back({std::chrono::high_resolution_clock::now(), point});
        if (mPoints.size() > kMaxPoints) {
            mPoints.erase(mPoints.begin());
        }
        
        auto& last = mPoints[mPoints.size() - 1];
        auto& first = mPoints[0];
        
        std::chrono::duration<double> timeDiff = last.time - first.time;
        double time = timeDiff.count();
        Vec2 distance = last.point - first.point;
        
        if (distance.length() > 1) {
            mCurrentVelocity = distance / time;
        } else {
            mCurrentVelocity = Vec2();
        }
    }
}