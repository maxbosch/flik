//
//  LocalizedString.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/10/16.
//
//

#pragma once

#include "cocos2d.h"
#include "format.h"

namespace flik
{
    class LocalizedString
    {
    public:
        static void loadStrings(const std::string& locale = "");
        
        static std::string getString(const std::string& key);
    
        template <typename... Args>
        static std::string getString(const std::string& key, const Args & ... args)
        {
            try {
                return fmt::sprintf(getString(key), args...);
            } catch (std::exception e){
            }
            
            return "";
        }
        
    private:
        
    };
}
