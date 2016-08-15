//
//  FLIKMailComposePresenter.h
//  Flik
//
//  Created by Adam Eskreis on 6/27/16.
//
//

#import <Foundation/Foundation.h>

@interface FLIKMailComposePresenter : NSObject

- (id)initWithAddress:(NSString *)toAddress subject:(NSString *)subject body:(NSString *)body;
- (void)presentInViewController:(UIViewController *)viewController;

@end
