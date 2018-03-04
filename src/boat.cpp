#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.02f;
    GLfloat vertex_buffer_data[9*2*10*11];
    double bentSine[11];

    for(int i=0; i<=10; ++i) {
        double ang = 0.8+((i/10.0)*(PI-0.8));
        bentSine[10-i] = 2*atan(sin(ang)/(2.0 - cos(ang)));
    }

    for(int i=0; i<10; ++i) {
        float prevyCord = ((i-5)/10.0);
        float yCord = ((i-4)/10.0);

        for(int j=0; j<10; ++j) {
            float prevxCord = (j-5);
            float xCord = (j-4);

            vertex_buffer_data[(18*11*i)+(18*j)+0] = prevxCord;
            vertex_buffer_data[(18*11*i)+(18*j)+1] = 4*bentSine[j]*(prevyCord);
            vertex_buffer_data[(18*11*i)+(18*j)+2] = 10 * prevyCord * prevyCord;

            vertex_buffer_data[(18*11*i)+(18*j)+3] = xCord;
            vertex_buffer_data[(18*11*i)+(18*j)+4] = 4*bentSine[j+1]*(yCord);
            vertex_buffer_data[(18*11*i)+(18*j)+5] = 10 * yCord * yCord;

            vertex_buffer_data[(18*11*i)+(18*j)+6] = prevxCord;
            vertex_buffer_data[(18*11*i)+(18*j)+7] = 4*bentSine[j]*(yCord);
            vertex_buffer_data[(18*11*i)+(18*j)+8] = 10 * yCord * yCord;

            vertex_buffer_data[(18*11*i)+(18*j)+9] = prevxCord;
            vertex_buffer_data[(18*11*i)+(18*j)+10] = 4*bentSine[j]*(prevyCord);
            vertex_buffer_data[(18*11*i)+(18*j)+11] = 10 * prevyCord * prevyCord;

            vertex_buffer_data[(18*11*i)+(18*j)+12] = xCord;
            vertex_buffer_data[(18*11*i)+(18*j)+13] = 4*bentSine[j+1]*(prevyCord);
            vertex_buffer_data[(18*11*i)+(18*j)+14] = 10 * prevyCord * prevyCord;

            vertex_buffer_data[(18*11*i)+(18*j)+15] = xCord;
            vertex_buffer_data[(18*11*i)+(18*j)+16] = 4*bentSine[j+1]*(yCord);
            vertex_buffer_data[(18*11*i)+(18*j)+17] = 10 * yCord * yCord;
        }

        vertex_buffer_data[(18*11*i)+(180)+0] = 5;
        vertex_buffer_data[(18*11*i)+(180)+1] = 4*bentSine[10]*(prevyCord);
        vertex_buffer_data[(18*11*i)+(180)+2] = 10 * prevyCord * prevyCord;

        vertex_buffer_data[(18*11*i)+(180)+3] = 5;
        vertex_buffer_data[(18*11*i)+(180)+4] = 0;
        vertex_buffer_data[(18*11*i)+(180)+5] = 10 * yCord * yCord;

        vertex_buffer_data[(18*11*i)+(180)+6] = 5;
        vertex_buffer_data[(18*11*i)+(180)+7] = 4*bentSine[10]*(yCord);
        vertex_buffer_data[(18*11*i)+(180)+8] = 10 * yCord * yCord;

        vertex_buffer_data[(18*11*i)+(180)+9] = 5;
        vertex_buffer_data[(18*11*i)+(180)+10] = 4*bentSine[10]*(prevyCord);
        vertex_buffer_data[(18*11*i)+(180)+11] = 10 * prevyCord * prevyCord;

        vertex_buffer_data[(18*11*i)+(180)+12] = 5;
        vertex_buffer_data[(18*11*i)+(180)+13] = 0;
        vertex_buffer_data[(18*11*i)+(180)+14] = 10 * prevyCord * prevyCord;

        vertex_buffer_data[(18*11*i)+(180)+15] = 5;
        vertex_buffer_data[(18*11*i)+(180)+16] = 0;
        vertex_buffer_data[(18*11*i)+(180)+17] = 10 * yCord * yCord;
    }

    this->object = create3DObject(GL_TRIANGLES, (sizeof(vertex_buffer_data)/(3*sizeof(vertex_buffer_data[0]))), vertex_buffer_data, color, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
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

void Boat::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boat::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    this->position.z -= speed;
    if(fabs(this->position.z) > 0.4) speed = -speed;
}

