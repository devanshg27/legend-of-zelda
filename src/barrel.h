#include "main.h"
#include "physics.h"

#ifndef BARREL_H
#define BARREL_H

class Barrel {
public:
    Barrel() {}
    Barrel(float x, float y, color_t color, color_t color2);
    glm::vec3 position;
    float speed;
    sphereBounding shape;
    sphereBounding shape2;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
    VAO *diamondObject1;
    VAO *diamondObject2;
};

#endif // BARREL_H
