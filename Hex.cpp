#include <cassert>
#include <string>

// Represented in axial coordinates
struct Hex {

    // q, r, s are equivalent to x,z,y in cubic coordinates
    // For axial coordinates, we can omit s and just calculate when needed
    const int q, r;

    Hex(int q_, int r_, int s_) : q(q_), r(r_) {
        assert(q_ + r_ + s_  == 0);
    }

    // Constructor with only two arguments for flexibility
    Hex(int q_, int r_) : q(q_), r(r_) {}

    // Accessors
    // Inline just copy-pastes function body to function calls
    inline int q() {return q;}
    inline int r() {return r;}
    inline int s() {return - q - r;}


};

int main(){

}