//
//  square.hpp
//

#ifndef square_hpp
#define square_hpp

#include <stdint.h>

#define RSQ1   100
#define BSQ1   100
#define GSQ1   10

#define RSQ2   100
#define BSQ2   10
#define GSQ2   100

#define RDEF   10
#define BDEF   50
#define GDEF   20

// bit flags
enum Direction : unsigned {
    TOP = 1 << 0, 
    BOTTOM = 1 << 1,
    LEFT = 1 << 2,
    RIGHT = 1 << 3, 
};

struct RGB{
    uint8_t r,g,b;
};

class Square{
    public:
    int posx;
    int posy;
    RGB color;
    unsigned dir;

    Square();
    ~Square() = default;
    Square(int x, int y);
    Square(int x, int y, Direction di);
    Square(int x, int y, RGB rgb);
    Square(int x, int y, RGB rgb, unsigned dir);

    bool isSamePos(Square sq);
    void nextPos();
};

#endif /* square_hpp */