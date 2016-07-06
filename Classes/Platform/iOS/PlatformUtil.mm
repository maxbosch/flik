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

#include <boost/format.hpp>

#include "PlatformUtil.h"
#import "FLIKMailComposePresenter.h"
#import "AppController.h"

namespace flik
{
    static const std::string kItunesBaseUrl = "https://itunes.apple.com/us/app/citymaps-discover-local-places/id%s";
    
    static inline NSString* toNSString(const std::string& str) {
        return [NSString stringWithUTF8String:str.c_str()];
    }
    
    void PlatformUtil::openURL(const std::string& url)
    {
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:toNSString(url)]];
    }
    
    std::string PlatformUtil::getStoreUrl()
    {
        NSString* appID = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleIdentifier"];
        return boost::str(boost::format(kItunesBaseUrl) % [appID UTF8String]);
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
        return [[[NSLocale preferredLanguages] objectAtIndex:0] UTF8String];
    }
}