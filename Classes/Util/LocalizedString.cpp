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
    static boost::property_tree::ptree sStrings;
    
    void LocalizedString::loadStrings(const std::string& inLocale)
    {
        auto locale = inLocale.length() > 0 ? inLocale : PlatformUtil::getLanguage();
        auto data = FileUtils::getInstance()->getStringFromFile("string/strings." + locale + ".json");
        std::stringstream stream(data);
        boost::property_tree::read_json(stream, sStrings);
    }
    
    std::string LocalizedString::getString(const std::string& key)
    {
        return sStrings.get<std::string>(key);
    }
}
