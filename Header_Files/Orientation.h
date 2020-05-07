#pragma once

#include "../Header_Files/Hex.h"

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
const Orientation orientation_pointy =
    Orientation(std::sqrt(3.0), std::sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0,
                std::sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0,
                0.5);

const Orientation orientation_flat =
    Orientation(3.0 / 2.0, 0.0, std::sqrt(3.0) / 2.0, std::sqrt(3.0),
                2.0 / 3.0, 0.0, -1.0 / 3.0, std::sqrt(3.0) / 3.0,
                0.0);

// Simple class to store the representation of a point
// Synonymous with pixel coordinates on a screen
struct Point {

    const double x, y;
    
    Point(double x_, double y_) : x(x_), y(y_) {}
};

// Will be used later to create the grid
struct Layout {
    
    const Orientation orientation;
    const Point size; // length from center of hexagon to vertex, size.x = size.y for regular hexagon
    const Point origin;
    
    Layout(Orientation orientation_, Point size_, Point origin_)
    :   orientation(orientation_), size(size_), origin(origin_) {}
};

// Translates hex coordinates (q, r, s) into pixel coordinates onto a screen
Point hex_to_pixel(Layout layout, Hex h) {

    // Matrix multiplication of forward matrix and hex coords
    // layout.size.x and y are not width and height of hexes
    const Orientation& M = layout.orientation;
    double x = (M.f0 * h.q + M.f1 * h.r) * layout.size.x;
    double y = (M.f2 * h.q + M.f3 * h.r) * layout.size.y;

    // Translate from origin
    return Point(layout.origin.x + x, layout.origin.y + y);
}

// Map cursor location on the screen to a specifc hex on the grid
FractionalHex pixel_to_hex(Layout layout, Point p){
    
    // Reversing hex_to_pixel algorithm
    const Orientation& M = layout.orientation;
    Point pt = Point((p.x - layout.origin.x) / layout.size.x,
                     (p.y - layout.origin.y) / layout.size.y);
    double q = M.b0 * pt.x + M.b1 * pt.y;
    double r = M.b2 * pt.x + M.b3 * pt.y;

    // Returns a fractional hex that will need to be rounded to a normal int-coordinate hex
    return FractionalHex(q, r, -q - r);
}

// Hex corners relative to the origin appear in 60 degree increments, w/ starting angle based on Orientation
// Exact pixel coordinates of the corners can be calculated by adding the coordinates of the center of the hex

// Returns how far the offset of a corner is from any given Hex coordinate
Point hex_corner_offset(Layout layout, int corner){

    Point size = layout.size;
    double angle = M_PI * (layout.orientation.start_angle + corner) / 3.0;
    return Point(size.x * cos(angle), size.y * sin(angle));
}

// Using the above corner offset method we can calculate a unique array of coordinates of the corners of any given Hex
std::vector<Point> hex_corners_coords(Layout layout, Hex h){

    std::vector<Point> corners;
    corners.reserve(6); // Every hex has 6 unique corners
    Point center_of_hex = hex_to_pixel(layout, h); // Calculate pixel coords of the center of the given Hex

    for(int i = 0; i < 6; i++){
        Point offset_from_center = hex_corner_offset(layout, i);
        corners.push_back(Point(center_of_hex.x + offset_from_center.x, 
                                center_of_hex.y + offset_from_center.y));
    }

    return corners;
}