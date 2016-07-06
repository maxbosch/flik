//
//  LocalizedString.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/10/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    class LocalizedString
    {
    public:
        static void loadStrings(const std::string& locale = "");
        
        static std::string getString(const std::string& key);
    };
}
