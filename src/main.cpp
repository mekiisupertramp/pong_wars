//
//  main.cpp
//
//  Created by Mehmed Blazevic on 24.04.2025.
//

#include <iostream>
#include <unistd.h>
#include <vector>
#include <queue>
#include <math.h>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <random>
#include <ctime>
#include "playground.hpp"
#include "graphic.hpp"


// default values
#define WIDTH   16
#define HEIGHT  16
#define PIXELSX 600
#define PIXELSY 600
#define SPEED   1000

using namespace std;

#define DEBUG


int main(int argc, char* argv[]) {
    int w = WIDTH;
    int h = HEIGHT;
    int pixelsX=PIXELSX;
    int pixelsY=PIXELSY;
    int speed=SPEED;
    bool start=false;

    // manage program's parameters first
    if(argc > 1){
        if(argc == 6){                        
            w = atoi(argv[1]);
            h = atoi(argv[2]);
            pixelsX = atoi(argv[3]);
            pixelsY = atoi(argv[4]);
            speed = atoi(argv[5]);
            cout << "w: " << w << " h: " << h << " pxsX: " << pixelsX << " pxsY: " << pixelsY << " speed: " << speed << endl;
        }else{
            cout << "Here is the arguments you must use." << endl;
            cout << "./main <squares in x> <squares in y> <width in pixels> <height in pixels> <period in ms>" << endl;
            return 0;
        }
    }    

    // Initialize SDL's video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    //Create a window
    SDL_Window* window = SDL_CreateWindow(
        "Pong war",             // window title
        SDL_WINDOWPOS_CENTERED,           // initial x position
        SDL_WINDOWPOS_CENTERED,           // initial y position
        pixelsX,                              // width, in pixels
        pixelsY,                              // height, in pixels
        SDL_WINDOW_SHOWN                  // flags
    );
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a renderer (hardware-accelerated)
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
      

    Playground* play = new Playground(w,h);
    Graphic* graph = new Graphic(window,renderer);
    //std::srand(std::time(nullptr)); 
    Square* sq1 = new Square(0, h/2, RGB{.r=RSQ1, .g=GSQ1, .b=BSQ1}, TOP | RIGHT);
    Square* sq2 = new Square(w-1, h/2, RGB{.r=RSQ2, .g=GSQ2, .b=BSQ2}, BOTTOM | LEFT);
    play->init(sq1,sq2);
    graph->render(play->getPixels(),h,w);


    SDL_Event e;
    bool running = true;
    while (running) {
        while(SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_QUIT: running = false; break;
                case SDL_KEYDOWN:
                    if (e.key.repeat == 0) {
                        switch (e.key.keysym.sym) {
                            case SDLK_SPACE: start=true; break;
                        }
                        
                    }
                break;
            }
        }
        if(start){
            cout << "yolo!" << endl;
            play->update(sq1,sq2);
            graph->render(play->getPixels(),h,w);
        }        
        SDL_Delay(speed);  // milliseconds
    }    

    delete play;
    delete sq1;
    delete sq2;
    delete graph;
    
    // Clean up    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}