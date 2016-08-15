//
//  LocalizedString.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/10/16.
//
//

#include "LocalizedString.h"
#include "PlatformUtil.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

USING_NS_CC;

namespace flik
{
    static std::string kDefaultLocale = "en";
    static boost::property_tree::ptree sStrings;
    
    void LocalizedString::loadStrings(const std::string& inLocale)
    {
        auto locale = inLocale.length() > 0 ? inLocale : PlatformUtil::getLanguage();
        auto files = FileUtils::getInstance();
        
        std::string data;
        if (files->isFileExist("string/strings." + locale + ".json")) {
            data = FileUtils::getInstance()->getStringFromFile("string/strings." + locale + ".json");
        } else {
            data = FileUtils::getInstance()->getStringFromFile("string/strings." + kDefaultLocale + ".json");
        }
        
        std::stringstream stream(data);
        boost::property_tree::read_json(stream, sStrings);
    }
    
    std::string LocalizedString::getString(const std::string& key)
    {
        return sStrings.get<std::string>(key);
    }
}
