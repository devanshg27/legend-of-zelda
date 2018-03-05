#include "booster.h"
#include "main.h"

Booster::Booster(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 2);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float length = 0.3f, breadth = 0.3f, depth = 1.5f;
    static GLfloat vertex_buffer_data[] = {
        -length, -breadth,-depth,
        -length, -breadth, 0.15f*depth,
        -length,  breadth, 0.15f*depth,
        length,  breadth,-depth,
        -length, -breadth,-depth,
        -length,  breadth,-depth,
        length, -breadth, 0.15f*depth,
        -length, -breadth,-depth,
        length, -breadth,-depth,
        length,  breadth,-depth,
        length, -breadth,-depth,
        -length, -breadth,-depth,
        -length, -breadth,-depth,
        -length,  breadth, 0.15f*depth,
        -length,  breadth,-depth,
        length, -breadth, 0.15f*depth,
        -length, -breadth, 0.15f*depth,
        -length, -breadth,-depth,
        -length,  breadth, 0.15f*depth,
        -length, -breadth, 0.15f*depth,
        length, -breadth, 0.15f*depth,
        length,  breadth, 0.15f*depth,
        length, -breadth,-depth,
        length,  breadth,-depth,
        length, -breadth,-depth,
        length,  breadth, 0.15f*depth,
        length, -breadth, 0.15f*depth,
        length,  breadth, 0.15f*depth,
        length,  breadth,-depth,
        -length,  breadth,-depth,
        length,  breadth, 0.15f*depth,
        -length,  breadth,-depth,
        -length,  breadth, 0.15f*depth,
        length,  breadth, 0.15f*depth,
        -length,  breadth, 0.15f*depth,
        length, -breadth, 0.15f*depth
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);

    this->shape = sphereBounding(this->position.x, this->position.y, this->position.z, 2.0f);
}

void Booster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * glm::rotate((float) (-45 * M_PI / 180.0f), glm::vec3(1, 0, 0)));
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * glm::rotate((float) (45 * M_PI / 180.0f), glm::vec3(1, 0, 0)));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);


    this->position.z += 1.5;
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate * glm::rotate((float) (-45 * M_PI / 180.0f), glm::vec3(1, 0, 0)));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * glm::rotate((float) (45 * M_PI / 180.0f), glm::vec3(1, 0, 0)));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    this->position.z -= 1.5;
}

void Booster::tick() {
    this->rotation += 0.5;
}