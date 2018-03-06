#include "chest.h"
#include "main.h"
#include "texture.h"

Chest::Chest(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    float length = 2.0f, breadth = 4.0f, depth = 4.0f;
    static GLfloat vertex_buffer_data[] = {
        -length, -breadth,0*-depth,
        -length, -breadth, depth,
        -length,  breadth, depth,
        length,  breadth,0*-depth,
        -length, -breadth,0*-depth,
        -length,  breadth,0*-depth,
        length, -breadth, depth,
        -length, -breadth,0*-depth,
        length, -breadth,0*-depth,
        length,  breadth,0*-depth,
        length, -breadth,0*-depth,
        -length, -breadth,0*-depth,
        -length, -breadth,0*-depth,
        -length,  breadth, depth,
        -length,  breadth,0*-depth,
        length, -breadth, depth,
        -length, -breadth, depth,
        -length, -breadth,0*-depth,
        -length,  breadth, depth,
        -length, -breadth, depth,
        length, -breadth, depth,
        length,  breadth, depth,
        length, -breadth,0*-depth,
        length,  breadth,0*-depth,
        length, -breadth,0*-depth,
        length,  breadth, depth,
        length, -breadth, depth,
        length,  breadth, depth,
        length,  breadth,0*-depth,
        -length,  breadth,0*-depth,
        length,  breadth, depth,
        -length,  breadth,0*-depth,
        -length,  breadth, depth,
        length,  breadth, depth,
        -length,  breadth, depth,
        length, -breadth, depth
    };

    depth = 0.3f;

    static GLfloat vertex_buffer_data2[] = {
        -length, -breadth,4.0f,
        -length, -breadth, 4.0f + depth,
        -length,  breadth, 4.0f + depth,
        length,  breadth,4.0f,
        -length, -breadth,4.0f,
        -length,  breadth,4.0f,
        length, -breadth, 4.0f + depth,
        -length, -breadth,4.0f,
        length, -breadth,4.0f,
        length,  breadth,4.0f,
        length, -breadth,4.0f,
        -length, -breadth,4.0f,
        -length, -breadth,4.0f,
        -length,  breadth, 4.0f + depth,
        -length,  breadth,4.0f,
        length, -breadth, 4.0f + depth,
        -length, -breadth, 4.0f + depth,
        -length, -breadth,4.0f,
        -length,  breadth, 4.0f + depth,
        -length, -breadth, 4.0f + depth,
        length, -breadth, 4.0f + depth,
        length,  breadth, 4.0f + depth,
        length, -breadth,4.0f,
        length,  breadth,4.0f,
        length, -breadth,4.0f,
        length,  breadth, 4.0f + depth,
        length, -breadth, 4.0f + depth,
        length,  breadth, 4.0f + depth,
        length,  breadth,4.0f,
        -length,  breadth,4.0f,
        length,  breadth, 4.0f + depth,
        -length,  breadth,4.0f,
        -length,  breadth, 4.0f + depth,
        length,  breadth, 4.0f + depth,
        -length,  breadth, 4.0f + depth,
        length, -breadth, 4.0f + depth
    };

    GLfloat cannon_vertex_buffer_data[9*2*2*10];
    breadth -= 0.1;
    length -= 0.1;

    for(int i=0; i<10; ++i) {
        double prevAng = (2*i*PI/10.0);
        double ang = (2*(i+1)*PI/10.0);
        cannon_vertex_buffer_data[(18*i)+0] = length*sin(prevAng);
        cannon_vertex_buffer_data[(18*i)+1] = -breadth;
        cannon_vertex_buffer_data[(18*i)+2] = 4.3f + length*cos(prevAng);

        cannon_vertex_buffer_data[(18*i)+3] = length*sin(ang);
        cannon_vertex_buffer_data[(18*i)+4] = breadth;
        cannon_vertex_buffer_data[(18*i)+5] = 4.3f + length*cos(ang);

        cannon_vertex_buffer_data[(18*i)+6] = length*sin(prevAng);
        cannon_vertex_buffer_data[(18*i)+7] = breadth;
        cannon_vertex_buffer_data[(18*i)+8] = 4.3f + length*cos(prevAng);

        cannon_vertex_buffer_data[(18*i)+9] =  length*sin(prevAng);
        cannon_vertex_buffer_data[(18*i)+10] = -breadth;
        cannon_vertex_buffer_data[(18*i)+11] =4.3f + length*cos(prevAng);

        cannon_vertex_buffer_data[(18*i)+12] = length*sin(ang);
        cannon_vertex_buffer_data[(18*i)+13] = -breadth;
        cannon_vertex_buffer_data[(18*i)+14] = 4.3f + length*cos(ang);

        cannon_vertex_buffer_data[(18*i)+15] = length*sin(ang);
        cannon_vertex_buffer_data[(18*i)+16] = breadth;
        cannon_vertex_buffer_data[(18*i)+17] = 4.3f + length*cos(ang);

        cannon_vertex_buffer_data[(18*10)+(18*i)+0] = 0;
        cannon_vertex_buffer_data[(18*10)+(18*i)+1] = breadth;
        cannon_vertex_buffer_data[(18*10)+(18*i)+2] = 4.3;

        cannon_vertex_buffer_data[(18*10)+(18*i)+3] = length*sin(ang);
        cannon_vertex_buffer_data[(18*10)+(18*i)+4] = breadth;
        cannon_vertex_buffer_data[(18*10)+(18*i)+5] = 4.3f + length*cos(ang);

        cannon_vertex_buffer_data[(18*10)+(18*i)+6] = length*sin(prevAng);
        cannon_vertex_buffer_data[(18*10)+(18*i)+7] = breadth;
        cannon_vertex_buffer_data[(18*10)+(18*i)+8] = 4.3f + length*cos(prevAng);

        cannon_vertex_buffer_data[(18*10)+(18*i)+9] =  0;
        cannon_vertex_buffer_data[(18*10)+(18*i)+10] =-breadth;
        cannon_vertex_buffer_data[(18*10)+(18*i)+11] = 4.3;

        cannon_vertex_buffer_data[(18*10)+(18*i)+12] = length*sin(ang);
        cannon_vertex_buffer_data[(18*10)+(18*i)+13] = -breadth;
        cannon_vertex_buffer_data[(18*10)+(18*i)+14] = 4.3f + length*cos(ang);

        cannon_vertex_buffer_data[(18*10)+(18*i)+15] = length*sin(prevAng);
        cannon_vertex_buffer_data[(18*10)+(18*i)+16] = -breadth;
        cannon_vertex_buffer_data[(18*10)+(18*i)+17] = 4.3f + length*cos(prevAng);
    }

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data2, color_t{255, 193, 7}, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, (sizeof(cannon_vertex_buffer_data)/(3*sizeof(cannon_vertex_buffer_data[0]))), cannon_vertex_buffer_data, color, GL_FILL);

}

void Chest::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

