#include "rock.h"
#include "main.h"

Rock::Rock(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    float length = 1.5f, breadth = 1.5f, depth = 1.5f;
    static GLfloat vertex_buffer_data[] = {
        -length, -breadth,-depth,
        0.5f*-length, -0.5f*breadth, depth,
        0.5f*-length,  0.5f*breadth, depth,
        length,  breadth,-depth,
        -length, -breadth,-depth,
        -length,  breadth,-depth,
        0.5f*length, -0.5f*breadth, depth,
        -length, -breadth,-depth,
        length, -breadth,-depth,
        length,  breadth,-depth,
        length, -breadth,-depth,
        -length, -breadth,-depth,
        -length, -breadth,-depth,
        0.5f*-length,  0.5f*breadth, depth,
        -length,  breadth,-depth,
        0.5f*length, -0.5f*breadth, depth,
        0.5f*-length, -0.5f*breadth, depth,
        -length, -breadth,-depth,
        0.5f*-length,  0.5f*breadth, depth,
        0.5f*-length, -0.5f*breadth, depth,
        0.5f*length, -0.5f*breadth, depth,
        0.5f*length,  0.5f*breadth, depth,
        length, -breadth,-depth,
        length,  breadth,-depth,
        length, -breadth,-depth,
        0.5f*length,  0.5f*breadth, depth,
        0.5f*length, -0.5f*breadth, depth,
        0.5f*length,  0.5f*breadth, depth,
        length,  breadth,-depth,
        -length,  breadth,-depth,
        0.5f*length,  0.5f*breadth, depth,
        -length,  breadth,-depth,
        0.5f*-length,  0.5f*breadth, depth,
        0.5f*length,  0.5f*breadth, depth,
        0.5f*-length,  0.5f*breadth, depth,
        0.5f*length, -0.5f*breadth, depth
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);

    this->shape = sphereBounding(this->position.x, this->position.y, this->position.z, 1.7f);
}

void Rock::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

