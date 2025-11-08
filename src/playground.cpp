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

Collision Playground::getCollision(Square* sq){
    return NONE;
}

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
void Playground::update(Square* sq1, Square* sq2){
    Square nxtSq1 = *sq1;
    Square nxtSq2 = *sq2;
    nxtSq1.nextPos();
    nxtSq2.nextPos();
    for(auto p: pixels){
        // check collisions
        // do something
        // then update colors ..
       if(p->isSamePos(nxtSq1)){p->color=sq1->color;}
       if(p->isSamePos(*sq1)){p->color=sq2->color;}
       if(p->isSamePos(nxtSq2)){p->color=sq2->color;}
       if(p->isSamePos(*sq2)){p->color=sq1->color;}
    }
    sq1->nextPos();
    sq2->nextPos();
}
