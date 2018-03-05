#include "aim.h"
#include "main.h"

Aim::Aim(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    float side = 0.2, thickness = 0.04;

    GLfloat vertex_buffer_data_display_hor[] = {
        -side, -thickness, 0,
        side, -thickness, 0,
        side,  thickness, 0,
        -side, thickness, 0,
    };

    this->object[0] = create3DObject(GL_TRIANGLE_FAN, 4, vertex_buffer_data_display_hor, color, GL_FILL);

    GLfloat vertex_buffer_data_display_ver[] = {
        -thickness, -side, 0,
        thickness, -side, 0,
        thickness,  side, 0,
        -thickness, side, 0,
    };
    this->object[1] = create3DObject(GL_TRIANGLE_FAN, 4, vertex_buffer_data_display_ver, color, GL_FILL);
}

void Aim::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0; i<sizeof(this->object)/sizeof(this->object[0]); ++i) {
        draw3DObject(this->object[i]);
    }
}

