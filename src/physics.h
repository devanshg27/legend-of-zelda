#include <utility>
#include "main.h"

#ifndef PHYSICS_H
#define PHYSICS_H

class sphereBounding {
public:
    sphereBounding() {}
    sphereBounding(float _x, float _y, float _z, float _radius);
    glm::vec3 position;
    float radius;
};

class boatBounding {
public:
    boatBounding() {}
    std::vector<glm::vec3> origPoints, points;
};

bool detect_collision(sphereBounding &sp, boatBounding &b);
bool detect_collision(sphereBounding &sp1, sphereBounding &sp2);

#endif // Physics_H