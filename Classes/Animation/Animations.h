//
//  Animations.hpp
//  Flik
//
//  Created by Adam Eskreis on 7/1/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    typedef std::function<void(float t)> AnimationStepFunction;
    typedef std::function<void(bool)> AnimationCompleteFunction;
    typedef std::function<float(float)> AnimationCurveFunction;
    
    static AnimationCurveFunction LinearCurve = [](float t) -> float {
        return t;
    };
    
    static AnimationCurveFunction QuadraticEaseInCurve = [](float t) -> float {
        return t * t;
    };
    
    static AnimationCurveFunction QuadraticEaseOutCurve = [](float t) -> float {
        return -t * (t - 2);
    };
    
    static AnimationCurveFunction QuadraticEaseInOutCurve = [](float t) -> float {
        if (t < 0.5) {
            return 2 * t *t;
        } else {
            return (-2 * t * t) + (4 * t) - 1;
        }
    };
    
    static AnimationCurveFunction OvershootCurve = [](float t) -> float {
        float tension = 2.0;
        
        t -= 1.0f;
        return t * t * ((tension + 1.0) * t + tension) + 1.0;
    };
    
    static AnimationCurveFunction AnticipateCurve = [](float t) -> float {
        float tension = 2.0;
        
        return t * t * ((tension + 1.0) * t - tension);
    };
    
    class AnimationNode;
    
    class Animations
    {
    public:
        static void animate(float duration, AnimationStepFunction step, AnimationCompleteFunction complete = nullptr,
                            AnimationCurveFunction curve = LinearCurve);
        
        static void onSceneChanged(cocos2d::Scene* scene);
    };
}
