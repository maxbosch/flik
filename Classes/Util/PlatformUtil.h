//
//  PlatformUtil.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/23/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    class PlatformUtil
    {
    public:
        static void openURL(const std::string& url);
        static std::string getStoreUrl();
        static void presentEmailCompose(const std::string& toAddress, const std::string& subject, const std::string& body);
        static std::string getLanguage();
    };
}
