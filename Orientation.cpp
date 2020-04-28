#include <cmath>

// Need a way to convert between hex and screen coordinates
// Two types of layouts based on how hexagons are laid on the screen
// Pointy top and flat top hex layout

struct Orientation{

    const double f0, f1, f2, f3; // 2x2 forward matrix
    const double b0, b1, b2, b3; // 2x2 inverse matrix (back)
    const double start_angle; // Multiples of 60 degrees

    Orientation(double f0_, double f1_, double f2_, double f3_,
                double b0_, double b1_, double b2_, double b3_,
                double start_angle_)
    :   f0(f0_), f1(f1_), f2(f2_), f3(f3_),
        b0(b0_), b1(b1_), b2(b2_), b3(b3_),
        start_angle(start_angle_) {}
};

// Implementation of the two layouts (pointy and flat top)
const Orientation layout_pointy =
    Orientation(std::sqrt(3.0), std::sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0,
                std::sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0,
                0.5);

const Orientation layout_flat =
    Orientation(3.0 / 2.0, 0.0, std::sqrt(3.0) / 2.0, std::sqrt(3.0),
                2.0 / 3.0, 0.0, -1.0 / 3.0, std::sqrt(3.0) / 3.0,
                0.0);

// Simple class to store the representation of a point
struct Point {

    const double x, y;
    
    Point(double x_, double y_) : x(x_), y(y_) {}

};

// Will be used later to create the grid
struct Layout {
    
    const Orientation orientation;
    const Point size;
    const Point origin;
    
    Layout(Orientation orientation_, Point size_, Point origin_)
    :   orientation(orientation_), size(size_), origin(origin_) {}

};

