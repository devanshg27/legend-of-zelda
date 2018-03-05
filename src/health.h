#include "main.h"
#include "physics.h"

#ifndef HEALTH_H
#define HEALTH_H


class Health {
public:
    Health() {}
    Health(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    sphereBounding shape;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif // HEALTH_H
