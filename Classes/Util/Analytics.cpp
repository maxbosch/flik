//
//  Analytics.cpp
//  Flik
//
//  Created by Adam Eskreis on 11/2/16.
//
//

#include "Analytics.h"
#include "cocos2d.h"
#include "PlatformUtil.h"
#include "Version.h"

USING_NS_CC;

namespace flik
{
    void Analytics::logEvent(const std::string& eventName, PTree& attributes)
    {
        // Add global properties
        std::string clientId = UserDefault::getInstance()->getStringForKey("key_clientId", "");
        if (clientId.length() == 0) {
            clientId = PlatformUtil::newUUID();
            UserDefault::getInstance()->setStringForKey("key_clientId", clientId.c_str());
        }
        
        attributes.add("client_id", clientId);
        attributes.add("timestamp", (uint64_t) time(NULL));
        attributes.add("version", kVersion);
        
        logEventInternal(eventName, attributes);
    }
}
