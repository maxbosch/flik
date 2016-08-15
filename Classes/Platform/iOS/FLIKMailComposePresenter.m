//
//  FLIKMailComposePresenter.m
//  Flik
//
//  Created by Adam Eskreis on 6/27/16.
//
//

#import "FLIKMailComposePresenter.h"
#import <MessageUI/MessageUI.h>

@interface FLIKMailComposePresenter() <MFMailComposeViewControllerDelegate>

@property (strong, nonatomic) MFMailComposeViewController *mailComposeView;

@end

@implementation FLIKMailComposePresenter

- (id)initWithAddress:(NSString *)toAddress subject:(NSString *)subject body:(NSString *)body
{
    self = [super init];
    if (self) {
        MFMailComposeViewController *mailComposeView = [[MFMailComposeViewController alloc] init];
        [mailComposeView setMailComposeDelegate:self];
        [mailComposeView setSubject:subject];
        [mailComposeView setMessageBody:body isHTML:NO];
        if (toAddress) {
            [mailComposeView setToRecipients:@[toAddress]];
        }
        
        self.mailComposeView = mailComposeView;
    }
    return self;
}

- (void)presentInViewController:(UIViewController *)viewController
{
    if (![MFMailComposeViewController canSendMail]){
        return;
    }
    
    [viewController presentViewController:self.mailComposeView animated:YES completion:nil];
}

- (void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError *)error
{
    [self.mailComposeView dismissViewControllerAnimated:YES completion:nil];
}

@end
