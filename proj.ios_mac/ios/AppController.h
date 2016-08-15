#import <UIKit/UIKit.h>

#import "RootViewController.h"

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;

@end

