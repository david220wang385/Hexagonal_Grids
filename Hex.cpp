#include <cassert>
#include <string>

// https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates
// https://www.geeksforgeeks.org/templates-cpp/
// This template means the first is generic, second is always int
template <typename Number, int w>
struct _Hex {

    // q, r, s are equivalent to x,z,y in cubic coordinates
    // For axial coordinates, we can omit s and just calculate when needed
    // https://docs.microsoft.com/en-us/cpp/cpp/unions?view=vs-2019
    union {
        const Number v[3];
        struct {const int q, r, s; };
    };
    
    // Support both 2 and 3 argument constructors
    _Hex(int q_, int r_, int s_) : v{q_, r_, s_} {
        assert(q_ + r_ + s_  == 0);
    }
    _Hex(int q_, int r_) : v{q_, r_, - q_ - r_} {}

    // Accessors
    // Inline just copy-pastes function body to function calls
    inline int q_() {return v[0];}
    inline int r_() {return v[1];}
    inline int s_() {return v[2];}

};

// https://www.tutorialspoint.com/cprogramming/c_typedef.htm
// typedef essentially just defines a type like a macro
// Custom typedef's for algorithms later on
typedef _Hex<int, 1> Hex;
typedef _Hex<int, 0> HexDifference;
typedef _Hex<double, 1> FractionalHex;
typedef _Hex<double , 0> FractionalHexDifference;

// Equality btwn. hexes is just whether their coordinates are equal.
// Operator overloading
bool operator==(Hex a, Hex b){
    return a.q == b.q && a.r == b.r && a.s == b.s;
}

bool operator!=(Hex a, Hex b){
    return !(a == b);
}

// Coordinate arithmetic for hex grids based on Cartesian coords act just like vectors
// Addition, subtraction, integer scalar multiplication
Hex hex_add(Hex a, Hex b){
    return Hex(a.q + b.q, a.r + b.r, a.s + b.s);
}

Hex hex_subtract(Hex a, Hex b){
    return Hex(a.q + b.q, a.r + b.r, a.s + b.s);
}

Hex hex_multiply(Hex a, int k){
    return Hex(a.q * k, a.r * k, a.s * k);
}