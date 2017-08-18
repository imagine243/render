//
//  main.cpp
//  render
//
//  Created by chao on 2017/8/7.
//  Copyright © 2017年 chao. All rights reserved.
//

#include <iostream>

#include <SDL.h>


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "sdl begin!\n";
    int width = 640;
    int height = 480;
    uint32_t * pixels = new uint32_t[width * height];
    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (i > 300 && j > 300) {
                pixels[j * width + i] = 0x00ff0000;
            }
        }
    }
    
    SDL_Window * win = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_SWSURFACE);
    SDL_Renderer * renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
//    SDL_Surface * surface = sdl_crea
    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    
    
    SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(uint32_t));
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    
    
    SDL_Delay(3000);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    
    return 0;
}
