//
//  ValueAnimation.h
//  MapEngineLibraryIOS
//
//  Created by Eddie Kimmel on 11/4/14.
//  Copyright (c) 2014 Adam Eskreis. All rights reserved.
//

#pragma once

#include <vector>

#include "Animation.h"

namespace flik
{
    template <typename T>
    class ValueAnimation;
    
    template <typename T>
    using AnimationBlock = std::function<void(const ValueAnimation<T>*, const T& value)>;
    
    template<typename T>
    class ValueAnimation : public Animation
    {
    public:
        
        ValueAnimation(const T& start, const T& end, AnimationBlock<T> animator)
        :mStart(start), mEnd(end), mChange(mEnd - mStart), mAnimator(animator)
        {
        }
        
        virtual void Animate(double t)
        {
            T newValue = mStart + mChange * t;
            mAnimator(this, newValue);
        }
        
        const T& GetStart()
        {
            return mStart;
        }
        
        const T& GetEnd()
        {
            return mEnd;
        }
        
        const T& GetChange()
        {
            return mChange;
        }
        
    private:
        
        T mStart;
        T mEnd;
        T mChange;
        
        AnimationBlock<T> mAnimator;
    };
    
    typedef ValueAnimation<float> ValueAnimationf;
    typedef ValueAnimation<double> ValueAnimationd;
    typedef ValueAnimation<int> ValueAnimationi;
    typedef ValueAnimation<Point> ValueAnimationPoint;
    typedef ValueAnimation<Size> ValueAnimationSize;
}
