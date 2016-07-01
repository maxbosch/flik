//
//  Interpolators.h
//  MapEngineLibraryIOS
//
//  Created by Eddie Kimmel on 11/4/14.
//  Copyright (c) 2014 Adam Eskreis. All rights reserved.
//

#pragma once

namespace flik
{
    struct Interpolator
    {
        Interpolator(){}
        virtual ~Interpolator(){}
        virtual float operator()(float t) = 0;
        
        float Interpolate(float t)
        {
            return this->operator()(t);
        }
    };
    
    struct LinearInterpolator : public Interpolator
    {
        float operator()(float t)
        {
            return t;
        }
    };
    
    struct QuadraticEaseInInterpolator : public Interpolator
    {
        float operator()(float t)
        {
            return t * t;
        }
    };
    
    struct QuadraticEaseOutInterpolator : public Interpolator
    {
        float operator()(float t)
        {
            return -t * (t - 2);
        }
    };
    
    struct QuadraticEaseInOutInterpolator : public Interpolator
    {
        float operator()(float t)
        {
            if (t < 0.5)
            {
                return 2 * t * t;
            }
            else
            {
                return (-2 * t * t) + (4 * t) - 1;
            }
        }
    };
    
    struct OvershootInterpolator : public Interpolator
    {
        float tension = 2.0;

        float operator()(float t)
        {
            t -= 1.0f;
            return t * t * ((tension + 1.0) * t + tension) + 1.0;
        }
    };
    
    struct AnticipateInterpolator : public Interpolator
    {
        float tension = 2.0;
        
        float operator()(float t)
        {
            return t * t * ((tension + 1.0) * t - tension);
        }
    };
}
