#include "playground.hpp"
#include <vector>

#define DEBUG

Playground::Playground(int width, int height):width(width),height(height){
    std::srand(std::time(nullptr)); 
    for(int y=0 ; y<height ; y++){
        for(int x=0 ; x<width ; x++){
            if(x<width/2){
                pixels.push_back(new Square(x,y,RGB{.r=RSQ2,.g=GSQ2,.b=BSQ2}));
            }else{
                pixels.push_back(new Square(x,y,RGB{.r=RSQ1,.g=GSQ1,.b=BSQ1}));
            }
        }
    } 
}
Playground::~Playground(){
    for(auto p : pixels){
        delete p;
    }
}
const std::vector<Square*>& Playground::getPixels(){return pixels;}
int Playground::getWidth(){return width;}
int Playground::getHeigth(){return height;}


void Playground::init(Square* sq1, Square* sq2){
    for(auto p: pixels){
       if((p->posx==sq1->posx)&&(p->posy==sq1->posy)){
            p->color = sq1->color;
       }else{
        if((p->posx==sq2->posx)&&(p->posy==sq2->posy)){
            p->color = sq2->color; 
        }
       }
    }
}

void Playground::checkNeighbours(Square* sq1, Square* sq2){
    if(sq1->posx>0){
        // check left
        if(pixels[sq1->posx-1+sq1->posy*width]->color == sq1->color){
            pixels[sq1->posx-1+sq1->posy*width]->color = sq2->color;
            sq1->dir = (sq1->dir&~LEFT) | RIGHT;
        }
    }
    if(sq1->posx<width-1){
        // check right
        if(pixels[sq1->posx+1+sq1->posy*width]->color == sq1->color){
            pixels[sq1->posx+1+sq1->posy*width]->color = sq2->color;
            sq1->dir = (sq1->dir&~RIGHT) | LEFT;
        }
    }
    if(sq1->posy>0){
        // check up
        if(pixels[sq1->posx+((sq1->posy-1)*width)]->color == sq1->color){
            pixels[sq1->posx+((sq1->posy-1)*width)]->color = sq2->color;
            sq1->dir = (sq1->dir&~TOP) | BOTTOM;
        }        
    }
    if(sq1->posy<height-1){
        // check down
        if(pixels[sq1->posx+((sq1->posy+1)*width)]->color == sq1->color){
            pixels[sq1->posx+((sq1->posy+1)*width)]->color = sq2->color;
        }        
    }

    if(sq2->posx>0){
        // check left
        if(pixels[sq2->posx-1+sq2->posy*width]->color == sq2->color){
            pixels[sq2->posx-1+sq2->posy*width]->color = sq1->color;
            sq2->dir = (sq2->dir&~LEFT) | RIGHT;
        }
    }
    if(sq2->posx<width-1){
        // check right
        if(pixels[sq2->posx+1+sq2->posy*width]->color == sq2->color){
            pixels[sq2->posx+1+sq2->posy*width]->color = sq1->color;
            sq2->dir = (sq2->dir&~RIGHT) | LEFT;
        }
    }
    if(sq2->posy>0){
        // check up
        if(pixels[sq2->posx+((sq2->posy-1)*width)]->color == sq2->color){
            pixels[sq2->posx+((sq2->posy-1)*width)]->color = sq1->color;
            sq2->dir = (sq2->dir&~TOP) | BOTTOM;
        }        
    }
    if(sq2->posy<height-1){
        // check down
        if(pixels[sq2->posx+((sq2->posy+1)*width)]->color == sq2->color){
            pixels[sq2->posx+((sq2->posy+1)*width)]->color = sq1->color;
        }        
    }
}

void Playground::checkWalls(Square* sq){
    if((sq->posx==0)&&(sq->posy==0)) sq->dir = BOTTOM|RIGHT;
    if((sq->posx==width-1)&&(sq->posy==0)) sq->dir = BOTTOM|LEFT;
    if((sq->posx==0)&&(sq->posy==height-1)) sq->dir = TOP|RIGHT;
    if((sq->posx==width-1)&&(sq->posy==height-1)) sq->dir = TOP|LEFT;
    if(sq->posx==0) sq->dir = (sq->dir & ~LEFT) | RIGHT;
    if(sq->posx==width-1) sq->dir = (sq->dir & ~RIGHT) | LEFT;
    if(sq->posy==0) sq->dir = (sq->dir & ~TOP) | BOTTOM;
    if(sq->posy==height-1) sq->dir = (sq->dir & ~BOTTOM) | TOP;
}

void Playground::update(Square* sq1, Square* sq2){  
    pixels[sq1->posx+sq1->posy*width]->color = sq2->color;
    pixels[sq2->posx+sq2->posy*width]->color = sq1->color;
    checkNeighbours(sq1,sq2);
    checkWalls(sq1);
    checkWalls(sq2); 
    sq1->nextPos();
    sq2->nextPos();
    pixels[sq1->posx+sq1->posy*width]->color = sq1->color;
    pixels[sq2->posx+sq2->posy*width]->color = sq2->color;
}
