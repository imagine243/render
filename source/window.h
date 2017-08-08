//
//  window.h
//  render
//
//  Created by chao on 2017/8/7.
//  Copyright © 2017年 chao. All rights reserved.
//

#ifndef window_h
#define window_h

#include <cstdio>            // fprint function, stderr
#include "rutil.h"

static const int WindowWidth = 800;
static const int WindowHeight = 600;

class Window {
    SDL_Surface * _screen;
    
    int _width;
    int _height;
    bool _runing;
public:
    Window(int argc, char * argv[], int width=WindowWidth, int height = WindowHeight, const char * title = "render"){
        //init 
        if(SDL_Init(SDL_INIT_VIDEO) != 0){
            fprintf(stderr, "sdl init failed \n");
        }

        SDL_Surface * screen = SDL_SetVideoMode(width,height,32,SDL_SWSURFACE);
        if(screen == NULL){
            SDL_Quit();
            fprintf("SDL_SetVideoMode failed \n");
        }
        _screen = screen;

        SDL_WM_SetCaption(title, NULL);

        _width = width;
        _height = height;

        //canvas

        _runing = true;
    };

    virtual ~Window(){
        //clean resouce
    };

    void run()
    {
        while(_runing){
            SDL_LockSurface(_screen);
        }
    };

    void update(){

    };

    void updateInput()
    {

    };

    void clear(){

    };

    void draw(){

    }

    void show(){
        
    }

};
#endif /* window_h */
