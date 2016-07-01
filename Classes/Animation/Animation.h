//
//  Animation.h
//  MapEngineLibraryIOS
//
//  Created by Eddie Kimmel on 11/4/14.
//  Copyright (c) 2014 Adam Eskreis. All rights reserved.
//

#pragma once

#include <functional>
#include <memory>
#include "Interpolator.h"

namespace flik
{
    class Animation
    {
    public:
        
        Animation();
        virtual ~Animation(){}
        
        virtual void Update(double delta);
        void Start();
        void Cancel();
        void End();
        
        bool IsStarted() const { return mState != AnimationState_Created;}
        bool IsCancelled() const { return mState == AnimationState_Cancelled;}
        bool IsFinished() const { return mState == AnimationState_Finished;}
        
        Animation *SetDuration(double duration) { mDuration = duration; return this;}
        Animation *SetStartDelay(double delay) { mStartDelay = delay; return this;}
        
        double Duration() const { return mDuration;}
        double StartDelay() const { return mStartDelay;}
        
        Animation *SetInterpolationFunction(std::unique_ptr<Interpolator> interpolator)
        {
            mInterpolator = std::move(interpolator);
            return this;
        }
        
        void* GetTarget() const {
            return mTarget;
        }
        
        Animation* SetTarget(void *target)
        {
            mTarget = target;
            return this;
        }
        
        void SetCompletion(std::function<void(Animation *)>&& completion) {
            mCompletion = completion;
        }
        
    protected:
        
        virtual void Animate(double t) = 0;
        
    private:
        
        enum AnimationState
        {
            AnimationState_Created,
            AnimationState_Started,
            AnimationState_Cancelled,
            AnimationState_Finished
        };
        
        std::unique_ptr<Interpolator> mInterpolator = nullptr;
        std::function<void(Animation *)> mCompletion;
        
        AnimationState mState = AnimationState_Created;
        double mElapsedTime = 0.0;
        double mDuration = 0.3;
        double mStartDelay = 0.0;
        
        void *mTarget;
    };
}
