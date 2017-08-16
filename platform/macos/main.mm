//
//  main.mm
//  render
//
//  Created by chao on 2017/8/7.
//  Copyright © 2017年 chao. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "window.h"

int main(int argc, char * argv[])
{
    NSLog(@"hello");
    Window window(argc, argv);
    window.run();
    return 0;
}
