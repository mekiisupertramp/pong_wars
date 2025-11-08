//
//  playground.hpp
//

#ifndef playground_hpp
#define playground_hpp

#include <iostream>
#include <unistd.h>
#include <math.h>
#include <vector>
#include <random>
#include <ctime>
#include "square.hpp"

#define LC  255 // lines color

enum Collision{
    NONE, 
    WALL,
    TARGET    
};

class Playground{
    private: 
    int width;
    int height; 
    std::vector<Square*> pixels;

    public:
    Playground(int width, int height);
    ~Playground();

    void init(Square* sq1, Square* sq2);
    void update(Square* sq1, Square* sq2);    
    Collision getCollision(Square* sq);
    const std::vector<Square*>& getPixels();
    int getWidth();
    int getHeigth();
    int getDifficulty();
};


#endif /* playground_hpp */