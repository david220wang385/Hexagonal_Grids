#include <cassert>
#include <string>

// https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates
// https://www.geeksforgeeks.org/templates-cpp/
// This template means the first is generic, second is always int
template <typename Number, int w>
struct _Hex {

    // q, r, s are equivalent to x,z,y in cubic coordinates
    // For axial coordinates, we can omit s and just calculate when needed
    union {
        const Number v[3];
        struct {const int q, r, s; };
    }
    
    // Support both 2 and 3 argument constructors
    Hex(int q_, int r_, int s_) : v{q_, r_, s_} {
        assert(q_ + r_ + s_  == 0);
    }
    Hex(int q_, int r_) : v{q_, r_, - q - r} {}

    // Accessors
    // Inline just copy-pastes function body to function calls
    inline int q() {return v[0];}
    inline int r() {return v[1];}
    inline int s() {return v[2];}


};

// https://www.tutorialspoint.com/cprogramming/c_typedef.htm
// Custom typedef's for algorithms later on
typedef _Hex<int, 1> Hex;
typedef _Hex<int, 0> HexDifference;
typedef _Hex<double, 1> FractionalHex;
typedef _Hex<double , 0> FractionalHexDifference;

int main(){

}