#include "Hex.cpp"
#include <unordered_map>
#include <iostream>
// Experimenting with methods of storing hex maps

// https://stackoverflow.com/questions/4872809/in-c-what-does-template-mean
// https://www.geeksforgeeks.org/template-specialization-c/
// https://en.cppreference.com/w/cpp/language/operators
// https://www.cplusplus.com/reference/functional/hash/
// https://en.cppreference.com/w/cpp/utility/hash

// Overloading the std implementation of hash
namespace std {
    
    template <> // Need this line otherwise, you can't specify specific template specialization

    // Creating hash struct specialization for Hex objects (in order to use hash maps)
    struct hash<Hex> {

        // Hashable specializations use overloaded () operator to hash
        std::size_t operator()(const Hex& h) const {

            // Using int template specialization and () operator to hash q and r components of the Hex
            hash<int> int_hash;
            std::size_t hq = int_hash(h.q);
            std::size_t hr = int_hash(h.r);

            // https://www.boost.org/doc/libs/1_37_0/doc/html/hash/reference.html#boost.hash_combine
            // Adapting the boost library's hash_combine method to work with Hex objects
            return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
        }
    };
}

int main(){
    std::unordered_map<Hex, float> heights; // Hashmap of Hex objects
    heights[Hex(1, 2, -3)] = 4.3; // calls std::hash
    std::cout << heights[Hex(1, 2, -3)];
    return 0;
}
