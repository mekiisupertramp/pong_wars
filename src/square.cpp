#include "square.hpp"

Square::Square(): posx(0), posy(0), color(RGB{.r=RDEF, .g=BDEF, .b=GDEF}){}

Square::Square(int x, int y) : Square(){
    posx = x;
    posy = y;    
}
Square::Square(int x, int y, Direction di) : Square(x,y){
    color.r=RDEF; 
    color.b=BDEF; 
    color.g=GDEF;
    dir=di;    
}
Square::Square(int x, int y, RGB rgb) : Square(x,y){
    color = rgb;
}
Square::Square(int x, int y, RGB rgb, unsigned di):Square(x,y,rgb){
    dir=di;
}

bool Square::isSamePos(Square sq){
    return ((posx==sq.posx)&&(posy==sq.posy)) ? true:false;
}

void Square::nextPos(){
    switch (dir)
    {
        case TOP|LEFT:  posx--; posy--; break;
        case TOP|RIGHT: posx++; posy--; break;
        case BOTTOM|LEFT:  posx--; posy++; break;
        case BOTTOM|RIGHT: posx++; posy++; break;
    }
}