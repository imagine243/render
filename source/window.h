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
#include "canvas.h"
#include <SDL.h>

static const int WindowWidth = 800;
static const int WindowHeight = 600;

class Window {
    SDL_Surface * _screen;
    Canvas * _canvas;
    Mesh * _mesh;
    
    int _width;
    int _height;
    bool _runing;

	bool pressedW = false;
	bool pressedS = false;
	bool pressedA = false;
	bool pressedD = false;
	bool pressedUp = false;
	bool pressedDown = false;
	bool pressedLeft = false;
	bool pressedRight = false;
public:
    Window(int argc, char * argv[], int width=WindowWidth, int height = WindowHeight, const char * title = "render"){
        //init 
        if(SDL_Init(SDL_INIT_VIDEO) != 0){
            fprintf(stderr, "sdl init failed \n");
        }

        SDL_Surface * screen = SDL_SetVideoMode(width,height,32,SDL_SWSURFACE);
        if(screen == NULL){
            SDL_Quit();
            fprintf(stderr, "SDL_SetVideoMode failed \n");
        }
        _screen = screen;

        SDL_WM_SetCaption(title, NULL);

        _width = width;
        _height = height;

        //canvas
		_canvas = new Canvas((uint32_t *)screen->pixels, width, height);

        _runing = true;

		const char * modelPath = "illidan.gua3d";
		const char * texturePath = "illidan.guaimage";

		if (argc > 2) {
			modelPath = argv[1];
			texturePath = argv[2];
		}

		_mesh = new Mesh(modelPath, texturePath);
    };

    virtual ~Window(){
        //clean resouce
		delete _canvas;
		delete _mesh;
    };

    void run()
    {
        while(_runing){
            SDL_LockSurface(_screen);
        }

		updateInput();
		update();
		clear();
		draw();
		show();
    };

    void update(){
		static const float transform = 0.05;

		_mesh->rotation.x += pressedUp ? transform : 0;
		_mesh->rotation.x -= pressedDown ? transform : 0;
		_mesh->rotation.y += pressedLeft ? transform : 0;
		_mesh->rotation.y -= pressedRight ? transform : 0;

		_mesh->position.y += pressedW ? transform : 0;
		_mesh->position.y -= pressedS ? transform : 0;
		_mesh->position.x -= pressedA ? transform : 0;
		_mesh->position.x += pressedD ? transform : 0;
    };

    void updateInput()
    {
		SDL_Event event;
		while (SDL_PollEvent(&event))	
		{
			HandleEvent(&event);
		}
    };

    void clear(){
		_canvas->clear();
    };

    void draw(){
		_canvas->drawMash(*_mesh);
    }

    void show(){
		SDL_UnlockSurface(_screen);
		SDL_UpdateRect(_screen, 0, 0, 0, 0);
    }

	void quit() {
		_runing = false;
	}

	void onKeyEvent(const SDL_Event *event) {
		SDLKey key = (*event).key.keysym.sym;
		bool keyIsDown = (event->type == SDL_KEYDOWN);
		if (key == SDLK_ESCAPE) {
			quit();
		}
		else if (key == SDLK_UP) {
			pressedUp = keyIsDown;
		}
		else if (key == SDLK_DOWN) {
			pressedDown = keyIsDown;
		}
		else if (key == SDLK_LEFT) {
			pressedLeft = keyIsDown;
		}
		else if (key == SDLK_RIGHT) {
			pressedRight = keyIsDown;
		}
		else if (key == SDLK_w) {
			pressedW = keyIsDown;
		}
		else if (key == SDLK_s) {
			pressedS = keyIsDown;
		}
		else if (key == SDLK_a) {
			pressedA = keyIsDown;
		}
		else if (key == SDLK_d) {
			pressedD = keyIsDown;
		}
	}

	void onMouseEvent(const SDL_Event *event) {

	}
	
	void HandleEvent(const SDL_Event *event) {
		unsigned char eventType = event->type;

		if (eventType == SDL_QUIT) {
			quit();
		}
		else if (eventType == SDL_KEYDOWN || eventType == SDL_KEYUP)
		{
			onKeyEvent(event);
		}
		else if(eventType == SDL_MOUSEBUTTONDOWN)
		{
			onMouseEvent(event);
		}
	}

};
#endif /* window_h */
