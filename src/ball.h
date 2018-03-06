#include "main.h"
#include "physics.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color, float acc = 0.01);
    glm::vec3 position, velocity;
    sphereBounding shape;
    void draw(glm::mat4 VP);
    float acc;
    void tick();
private:
    VAO *object;
};

#endif // BALL_H
