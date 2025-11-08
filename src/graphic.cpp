#include "graphic.hpp"

Graphic::Graphic(SDL_Window* window, SDL_Renderer* renderer) : window(window), renderer(renderer){
    // Set draw color to black (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, 50, 0, 0, 255);
    // Clear the window (fills it with the draw color)
    SDL_RenderClear(renderer);
    // Show the cleared window
    SDL_RenderPresent(renderer);  
}

Graphic::~Graphic(){}    

void Graphic::render(const std::vector<Square*>& pixels, int width, int height){   
    int x, y;
    SDL_GetWindowSize(window, &x, &y);
    int pixWidth = x/width;
    int pixHeight = y/height;

    SDL_Rect rect = {.x=0, .y=0, .w=pixWidth, .h=pixHeight};
    for(auto p : pixels){
        rect.x = p->posx*pixWidth;
        rect.y = p->posy*pixHeight;
        SDL_SetRenderDrawColor(renderer, p->color.r, p->color.g, p->color.b, 255); 
        SDL_RenderFillRect(renderer,&rect);
        SDL_SetRenderDrawColor(renderer, LC, LC, LC, 255);
        SDL_RenderDrawRect(renderer,&rect); 
    }
    SDL_RenderPresent(renderer);
}