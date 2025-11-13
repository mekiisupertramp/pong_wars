//
//  square.hpp
//

#ifndef square_hpp
#define square_hpp

#include <stdint.h>

#define RSQ1   255
#define BSQ1   255
#define GSQ1   153

#define RSQ2   204
#define BSQ2   0
#define GSQ2   153

#define RDEF   10
#define BDEF   50
#define GDEF   20

// bit flags
enum Direction : uint8_t{
    TOP = 1 << 0, 
    BOTTOM = 1 << 1,
    LEFT = 1 << 2,
    RIGHT = 1 << 3, 
};

struct RGB{
    uint8_t r,g,b;

    bool operator==(const RGB& other) const {
        return r == other.r && g == other.g && b == other.b;
    }
    bool operator!=(const RGB& other) const {
        return r != other.r || g != other.g || b != other.b;
    }
};

class Square{
    public:
    int posx;
    int posy;
    RGB color;
    unsigned dir;

    Square();
    ~Square() = default;
    Square(const Square& other);
    Square& operator=(const Square& other);
    Square(int x, int y);
    Square(int x, int y, Direction di);
    Square(int x, int y, RGB rgb);
    Square(int x, int y, RGB rgb, unsigned dir);

    bool isSamePos(Square sq);
    void nextPos();
};

#endif /* square_hpp */
