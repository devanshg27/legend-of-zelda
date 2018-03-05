#include "physics.h"
#include "main.h"

sphereBounding::sphereBounding(float _x, float _y, float _z, float _radius) {
    this->position = glm::vec3(_x, _y, _z);
    this->radius = _radius;
}

bool detect_collision(sphereBounding &sp, boatBounding &b) {
    for(auto&z: b.points) {
        if(glm::length(z - sp.position) < sp.radius) {
            return true;
        }
    }
    return false;
}

bool detect_collision(sphereBounding &sp1, sphereBounding &sp2) {
    return glm::length(sp1.position - sp2.position) < sp1.radius + sp2.radius;
}