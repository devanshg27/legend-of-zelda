#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, color_t color, color_t baseColor);
    glm::vec3 position;
    GLuint Texture;
    float rotation;
    float velocity, upVelocity;
    void draw(glm::mat4 VP);
    void texturedDraw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *mastObject;
    VAO *sailObject;
    VAO *baseObject;
};

#endif // BOAT_H
