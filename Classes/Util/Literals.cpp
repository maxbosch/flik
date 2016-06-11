//
//  Literals.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/7/16.
//
//

#include "Literals.h"

namespace flik
{
    static const double kDPIScaleFactor = (1.0 / 160.0);
    
    long double operator "" _dp(long double value)
    {
        return value * 2;
    }
}
