#include "Sector.h"

Sector::Sector(int x, int y, int z) : x(x), y(y), z(z), left(nullptr), right(nullptr), parent(nullptr), color(RED) {
        distance_from_earth = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        //floor of the distance
        int floor_distance = floor(distance_from_earth);
        //sector code
        std::string x_code = if (x < 0) ? "L" : (x > 0) ? "R" : "S";
        std::string y_code = if (y < 0) ? "D" : (y > 0) ? "U" : "S";
        std::string z_code = if (z < 0) ? "B" : (z > 0) ? "F" : "S";
        sector_code =  std::to_string(floor_distance) + x_code + y_code + z_code;
}

Sector::~Sector() {
}

Sector& Sector::operator=(const Sector& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        distance_from_earth = other.distance_from_earth;
        sector_code = other.sector_code;
        left = other.left;
        right = other.right;
        parent = other.parent;
        color = other.color;
    }
    return *this;
}

bool Sector::operator==(const Sector& other) const {
    return (x == other.x && y == other.y && z == other.z);
}

bool Sector::operator!=(const Sector& other) const {
    return !(*this == other);
}

bool Sector::operator<(const Sector& other) const {
    return (x < other.x || (x == other.x && y < other.y) || (x == other.x && y == other.y && z < other.z));
}

bool Sector::operator>(const Sector& other) const {
    return (x > other.x || (x == other.x && y > other.y) || (x == other.x && y == other.y && z > other.z));
}

bool Sector::operator<=(const Sector& other) const {
    return (*this < other || *this == other);
}

bool Sector::operator>=(const Sector& other) const {
    return (*this > other || *this == other);
}