#include "main.h"
#include "physics.h"

#ifndef ROCK_H
#define ROCK_H


class Rock {
public:
    Rock() {}
    Rock(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    sphereBounding shape;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif // ROCK_H
