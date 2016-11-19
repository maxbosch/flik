//
//  PlatformUtil.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/23/16.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>

#include "PlatformUtil.h"
#import "FLIKMailComposePresenter.h"
#import "AppController.h"
#include "format.h"

namespace flik
{
    static NSString *kItunesBaseUrl = @"https://itunes.apple.com/us/app/citymaps-discover-local-places/id%@";
    
    static inline NSString* toNSString(const std::string& str) {
        return [NSString stringWithUTF8String:str.c_str()];
    }
    
    void PlatformUtil::openURL(const std::string& url)
    {
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:toNSString(url)]];
    }
    
    std::string PlatformUtil::getStoreUrl()
    {
        NSString* appID = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"AppStoreId"];
        return [[NSString stringWithFormat:kItunesBaseUrl, appID] UTF8String];
    }
    
    void PlatformUtil::presentEmailCompose(const std::string& toAddress, const std::string& subject, const std::string& body)
    {
        FLIKMailComposePresenter *presenter = [[FLIKMailComposePresenter alloc] initWithAddress:toNSString(toAddress)
                                                                                        subject:toNSString(subject)
                                                                                           body:toNSString(body)];
        
        auto activeVC = ((AppController *)[UIApplication sharedApplication].delegate).viewController;
        [presenter presentInViewController:activeVC];
    }
    
    std::string PlatformUtil::getLanguage()
    {
        NSString *language = [[NSLocale preferredLanguages] objectAtIndex:0];
        return [[language substringToIndex:2] UTF8String];
    }
    
    std::string PlatformUtil::newUUID()
    {
        return [[[[NSUUID UUID] UUIDString] lowercaseString] UTF8String];
    }
}
