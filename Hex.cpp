#include <cassert>
#include <string>
#include <vector>
#include <cmath>

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
        struct {const Number q, r, s; };
    };
    
    // Support both 2 and 3 argument constructors
    // Need to template constructor to support double values for fractional hexes
    _Hex(Number q_, Number r_, Number s_) : v{q_, r_, s_} {
        assert(q_ + r_ + s_  <= 0.0000001); // bounds check in case of double
    }
    _Hex(Number q_, Number r_) : v{q_, r_, - q_ - r_} {}

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

/* Calculating distance btwn. two hexes
   This implementation is based on the conversion btwn. cube and hex grids
   Another implementation relies on finding the max of the three differential components
   But this implementation is slightly more efficient, since dividing by 2 is just a bitshift operation
   Graphic explanation in reference_material folder
*/
int hex_length(Hex hex){
    return int((abs(hex.q) + abs(hex.r) + abs(hex.s)) / 2);
}

int hex_distance(Hex a, Hex b){
    return hex_length(hex_subtract(a, b));
}


// https://www.redblobgames.com/grids/hexagons/#neighbors
const std::vector<Hex> hex_adjacents = {
    Hex(1, 0, -1), Hex(1, -1, 0), Hex(0, -1, 1),
    Hex(-1, 0, 1), Hex(-1, 1, 0), Hex(0, 1, -1)
};

// https://stackoverflow.com/questions/1571340/what-is-the-assert-function
// Return a unit hex (directional hex) with range [0,5] based on direction from origin
Hex hex_adj_direction(int direction){
    assert(0 <= direction && direction < 6);
    return hex_adjacents[direction];
}

// Find neighboring hexes (generate coords for neighboring hexes)
Hex hex_adjacent_neighbor(Hex hex, int direction){
    return hex_add(hex, hex_adj_direction(direction));
}

// Change one axis by +/-2 and the other two axes by -/+1 (total change must be zero)
const std::vector<Hex> hex_diagonals = {
    Hex(+2, -1, -1), Hex(+1, +1, -2), Hex(-1, +2, -1), 
    Hex(-2, +1, +1), Hex(-1, -1, +2), Hex(+1, -2, +1), 
};

Hex hex_diag_direction(int direction){
    assert(0 <= direction && direction < 6);
    return hex_diagonals[direction];
}

// Find diagonally neighboring hexes (generate coords for diag. neighboring hexes)
Hex hex_diagonal_neighbor(Hex hex, int direction){
    return hex_add(hex, hex_diag_direction(direction));
}

// Round a FractionalHex to the nearest integer Hex
// https://www.redblobgames.com/grids/hexagons/#map-storage
Hex hex_round(FractionalHex h){

    // Basic rounding
    int q = int(round(h.q));
    int r = int(round(h.r));
    int s = int(round(h.s));

    double q_diff = abs(q - h.q);
    double r_diff = abs(r - h.r);
    double s_diff = abs(s - h.s);

    // Minimize deviation 


    return Hex(q, r, s);
}