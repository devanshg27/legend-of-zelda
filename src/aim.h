#include "main.h"

#ifndef AIM_H
#define AIM_H


class Aim {
public:
    Aim() {}
    Aim(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
private:
    VAO *object[2];
};

#endif // AIM_H
