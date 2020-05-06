#pragma once

#include <cassert>
#include <vector>
#include <cmath>
#include <iostream>

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

    // Minimize deviation in order to uphold (q + r + s = 0)
    if (q_diff > r_diff and q_diff > s_diff) {
        q = -r - s;
    } else if (r_diff > s_diff) {
        r = -q - s;
    } else {
        s = -q - r;
    }

    return Hex(q, r, s);
}

// Drawing a line on hex grid using linear interpolation
// https://www.redblobgames.com/grids/line-drawing.html
// https://www.youtube.com/watch?v=8uLVnM36XUc

// Simply 1-D lerp function
float lerp(double a, double b, double t){
    return a * (1-t) + b * t;
}

// Applying above lerp function to each of the components
FractionalHex hex_lerp (FractionalHex a, FractionalHex b, double t){
    return FractionalHex(lerp(a.q, b.q, t),
                         lerp(a.r, b.r, t),
                         lerp(a.s, b.s, t));
}

// Drawing the line
std::vector<Hex> hex_line(Hex a, Hex b){

    int N = hex_distance(a, b); // Number of hexes to include in the line (not counting beginning hex)

    // Needed in case hex_lerp returns a Hex on the edge
    // Nudges all components of each in the same direction
    FractionalHex a_nudge(a.q + 1E-6, a.r + 1E-6, a.s - 2E-6);
    FractionalHex b_nudge(b.q + 1E-6, b.r + 1E-6, b.s - 2E-6);

    std::vector<Hex> results;
    results.reserve(N+1);

    double step = 1.0 / std::max(N, 1); // max function needed for lines w/ length 0, (a == b)

    // Start at 0 and end at N b/c the line includes both input hexes
    for(int i = 0; i <= N; i++){
        results.push_back(hex_round(hex_lerp(a_nudge, b_nudge, step * i)));
    }

    return results; // return a list of hexes included in the line
}

// Return a list of Hexes within N distance of the given hex
// std::vector<Hex> range(Hex h, int range){
//     return std::vector<Hex>;
// }