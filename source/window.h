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
    Canvas * _canvas;
    Mesh * _mesh;
    uint32_t * pixels;
    
    SDL_Renderer * renderer;
    SDL_Texture * texture;
    SDL_Window * win;
    
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
    Window(int argc, const char * argv[], int width=WindowWidth, int height = WindowHeight, const char * title = "render"){
//        //init 
//        if(SDL_Init(SDL_INIT_VIDEO) != 0){
//            fprintf(stderr, "sdl init failed \n");
//        }

//        SDL_Surface * screen = SDL_SetVideoMode(width,height,32,SDL_SWSURFACE);
//        if(screen == NULL){
//            SDL_Quit();
//            fprintf(stderr, "SDL_SetVideoMode failed \n");
//        }
//        _screen = screen;
        
        win = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_SWSURFACE);
        renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
        
        

//        SDL_WM_SetCaption(title, NULL);

        _width = width;
        _height = height;
        
        pixels = new uint32_t[_width * _height];

        //canvas
		_canvas = new Canvas((uint32_t *)pixels, width, height);

        _runing = true;

		const char * modelPath = "cube.3d";
//        const char * modelPath = "illidan.gua3d";
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
        delete [] pixels;
    };

    void run()
    {
        while(_runing){
//            SDL_LockSurface(_screen);
            updateInput();
            update();
            draw();
            clear();
            show();
        }
        
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
    };
    
    void clear(){
        SDL_RenderClear(renderer);
    };
    
    void draw(){
        _canvas->clear();
        
        
        		_canvas->drawMash(*_mesh);
        
//         //draw line
//                Vertex ver1 = Vertex(vector(), vector(), 0.0f, 0.0f, color(1.0f,0.0f,0.0f,1.0f));
//                Vertex ver2 = Vertex(vector(100.0f, 100.0f, 0.0f), vector(), 0.0f,0.0f);
//                _canvas->drawLine(ver1, ver2);
        
//        // draw Triangle
//        Vertex ver1 = Vertex(vector(400.0f,300.0f,0.5f), vector(), 0.0f, 0.0f, color(1.0f,0.0f,0.0f,1.0f));
//        Vertex ver2 = Vertex(vector(414.0f, 300.0f, 0.5f), vector(), 0.0f,0.0f,color(0.0f,1.0f,0.0f,1.0f));
//        Vertex ver3 = Vertex(vector(414.0f, 289.0f, 0.5f), vector(), 0.0f,0.0f,color(0.0f,0.0f,1.0f,1.0f));
//        _canvas->drawTriangle(ver1, ver2, ver3, NULL);
        
        // draw cube
        
        
        SDL_UpdateTexture(texture, NULL, pixels, _width * sizeof(uint32_t));
    };
    
    void show(){
        //		SDL_UnlockSurface(_screen);
        //		SDL_UpdateRect(_screen, 0, 0, 0, 0);
        
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
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



	void quit() {
		_runing = false;
    };

	void onKeyEvent(const SDL_Event *event) {
		SDL_Keycode key = (*event).key.keysym.sym;
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
    };

	void onMouseEvent(const SDL_Event *event) {

    };
	
	void HandleEvent(const SDL_Event *event) {
		Uint32 eventType = event->type;

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
    };

};
#endif /* window_h */
