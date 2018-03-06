#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color, float acc) {
    this->position = glm::vec3(x, y, -100);
    this->acc = acc;
    GLfloat vertex_buffer_data[9*2*10*10];

    float radius = 0.5;

    for(int i=0; i<10; ++i) {
        float prevyAng = (i*PI/10.0);
        float yAng = ((i+1)*PI/10.0);

        for(int j=0; j<10; ++j) {
            double prevAng = (2*j*PI/10.0);
            double ang = (2*(j+1)*PI/10.0);

            vertex_buffer_data[(18*10*i)+(18*j)+0] = radius * sin(prevyAng) *cos(prevAng);
            vertex_buffer_data[(18*10*i)+(18*j)+1] = radius * sin(prevyAng) *sin(prevAng);
            vertex_buffer_data[(18*10*i)+(18*j)+2] = radius * cos(prevyAng);

            vertex_buffer_data[(18*10*i)+(18*j)+3] = radius * sin(yAng) *cos(ang);
            vertex_buffer_data[(18*10*i)+(18*j)+4] = radius * sin(yAng) *sin(ang);
            vertex_buffer_data[(18*10*i)+(18*j)+5] = radius * cos(yAng);

            vertex_buffer_data[(18*10*i)+(18*j)+6] = radius * sin(yAng) *cos(prevAng);
            vertex_buffer_data[(18*10*i)+(18*j)+7] = radius * sin(yAng) *sin(prevAng);
            vertex_buffer_data[(18*10*i)+(18*j)+8] = radius * cos(yAng);

            vertex_buffer_data[(18*10*i)+(18*j)+9] = radius * sin(prevyAng) *cos(prevAng);
            vertex_buffer_data[(18*10*i)+(18*j)+10] =radius * sin(prevyAng) *sin(prevAng);
            vertex_buffer_data[(18*10*i)+(18*j)+11] = radius * cos(prevyAng);

            vertex_buffer_data[(18*10*i)+(18*j)+12] = radius * sin(prevyAng) *cos(ang);
            vertex_buffer_data[(18*10*i)+(18*j)+13] = radius * sin(prevyAng) *sin(ang);
            vertex_buffer_data[(18*10*i)+(18*j)+14] = radius * cos(prevyAng);

            vertex_buffer_data[(18*10*i)+(18*j)+15] = radius * sin(yAng) *cos(ang);
            vertex_buffer_data[(18*10*i)+(18*j)+16] = radius * sin(yAng) *sin(ang);
            vertex_buffer_data[(18*10*i)+(18*j)+17] = radius * cos(yAng);
        }

    }

    this->shape = sphereBounding(this->position.x, this->position.y, this->position.z, radius);
    this->object = create3DObject(GL_TRIANGLES, (sizeof(vertex_buffer_data)/(3*sizeof(vertex_buffer_data[0]))), vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::tick() {
    this->position += this->velocity;
    this->velocity.z -= this->acc;
    this->shape.position = this->position;
}

