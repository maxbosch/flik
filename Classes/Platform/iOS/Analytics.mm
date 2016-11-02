//
//  Answers.cpp
//  Flik
//
//  Created by Adam Eskreis on 11/1/16.
//
//

#include <stdio.h>
#include "Analytics.h"

#import <Foundation/Foundation.h>
#import <Crashlytics/Answers.h>

namespace flik
{
    void Analytics::logEventInternal(const std::string& eventName, boost::property_tree::ptree& attributes)
    {
        // Add OS Specific attributes
        attributes.add("os", "ios");
        attributes.add("os_version", std::string([[UIDevice currentDevice].systemVersion UTF8String]));
        
        NSMutableDictionary *attributesDict = [NSMutableDictionary new];
        
        for (auto& attribute : attributes) {
            auto number = attribute.second.get_value_optional<double>();
            if (number) {
                [attributesDict setValue:[NSNumber numberWithDouble:number.get()]
                                  forKey:[NSString stringWithUTF8String:attribute.first.c_str()]];
            } else {
                auto string = attribute.second.get_value_optional<std::string>();
                if (string) {
                    [attributesDict setValue:[NSString stringWithUTF8String:string.get().c_str()]
                                      forKey:[NSString stringWithUTF8String:attribute.first.c_str()]];
                }
            }
        }
        
        NSString *eventNameObjC = [NSString stringWithUTF8String:eventName.c_str()];
        [Answers logCustomEventWithName:eventNameObjC customAttributes:attributesDict];
        
#if COCOS2D_DEBUG
        NSLog(@"Analytics Event: %@, attributes: %@", eventNameObjC, attributesDict);
#endif
    }
}
