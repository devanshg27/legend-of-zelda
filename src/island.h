#include "main.h"

#ifndef ISLAND_H
#define ISLAND_H

class Island {
public:
    Island() {}
    Island(float x, float y, color_t color, color_t color2);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif // ISLAND_H
