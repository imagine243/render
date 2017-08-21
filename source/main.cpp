//
//  main.cpp
//  render
//
//  Created by chao on 2017/8/7.
//  Copyright © 2017年 chao. All rights reserved.
//

#include <iostream>
#include "window.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, render!\n";
    Window win = Window(argc,argv);
    win.run();
    return 0;
}
