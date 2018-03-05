#include "main.h"
#include "physics.h"

#ifndef BOOSTER_H
#define BOOSTER_H


class Booster {
public:
    Booster() {}
    Booster(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    sphereBounding shape;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif // BOOSTER_H
