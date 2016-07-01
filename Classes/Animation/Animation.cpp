//
//  Animation.cpp
//  MapEngineLibraryIOS
//
//  Created by Eddie Kimmel on 11/4/14.
//  Copyright (c) 2014 Adam Eskreis. All rights reserved.
//

#include "Animation.h"
#include "Interpolator.h"

namespace flik
{
    Animation::Animation()
    :mInterpolator(new LinearInterpolator())
    {
    }
    
    void Animation::Start()
    {
        if (!this->IsStarted())
        {
            mState = AnimationState_Started;
        }
    }
    
    void Animation::Cancel()
    {
        mState = AnimationState_Cancelled;
        if (mCompletion != nullptr) {
            mCompletion(this);
        }
    }
    
    void Animation::End()
    {
        mState = AnimationState_Finished;
        if (mCompletion != nullptr) {
            mCompletion(this);
        }
    }
    
    void Animation::Update(double delta)
    {
        mElapsedTime += delta;
        double elapsedAnimationTime = mElapsedTime - mStartDelay;
        if (!this->IsCancelled() && elapsedAnimationTime > 0)
        {
            double linearT = mDuration < 0.01 ? 1.0 : elapsedAnimationTime / mDuration;
            bool finished = linearT >= 1.0;
            if (this->IsFinished() || finished)
            {
                this->End();
                linearT = 1.0;
            }
            double curvedT = mInterpolator->Interpolate(linearT);
            this->Animate(curvedT);
        }
    }
}