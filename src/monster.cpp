#include "monster.h"
#include "main.h"

Monster::Monster(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 2);
    this->rotation = 0;
    GLfloat vertex_buffer_data[9*2*10*10];
    GLfloat mouth_vertex_buffer_data[9*2*10*10];
    GLfloat thorn_vertex_buffer_data[9*2*2*10];
    GLfloat cannon_vertex_buffer_data[9*2*2*10];
    float length = 0.3f, breadth = 3.5f, depth = 0.3f;
    static GLfloat leg_vertex_buffer_data[] = {
        -length, -breadth,-depth,
        -length, -breadth, depth,
        -length,  breadth, depth,
        length,  breadth,-depth,
        -length, -breadth,-depth,
        -length,  breadth,-depth,
        length, -breadth, depth,
        -length, -breadth,-depth,
        length, -breadth,-depth,
        length,  breadth,-depth,
        length, -breadth,-depth,
        -length, -breadth,-depth,
        -length, -breadth,-depth,
        -length,  breadth, depth,
        -length,  breadth,-depth,
        length, -breadth, depth,
        -length, -breadth, depth,
        -length, -breadth,-depth,
        -length,  breadth, depth,
        -length, -breadth, depth,
        length, -breadth, depth,
        length,  breadth, depth,
        length, -breadth,-depth,
        length,  breadth,-depth,
        length, -breadth,-depth,
        length,  breadth, depth,
        length, -breadth, depth,
        length,  breadth, depth,
        length,  breadth,-depth,
        -length,  breadth,-depth,
        length,  breadth, depth,
        -length,  breadth,-depth,
        -length,  breadth, depth,
        length,  breadth, depth,
        -length,  breadth, depth,
        length, -breadth, depth
    };

    float radius = 1.75;

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

    radius += 0.01f;

    for(int i=0; i<10; ++i) {
        float prevyAng = (i*(PI/5.0f)/10.0) + PI/2;
        float yAng = ((i+1)*(PI/5.0f)/10.0) + PI/2;

        for(int j=0; j<10; ++j) {
            double prevAng = ((j-5)*(PI)/20.0) * ((12 - i) / 12.0);
            double ang = ((j-4)*(PI)/20.0) * ((12 - i) / 12.0);

            double prevAngUpper = ((j-5)*(PI)/20.0) * ((12 - i + 1) / 12.0);
            double angUpper = ((j-4)*(PI)/20.0) * ((12 - i + 1) / 12.0);

            mouth_vertex_buffer_data[(18*10*i)+(18*j)+0] = radius * sin(prevyAng) *cos(prevAng);
            mouth_vertex_buffer_data[(18*10*i)+(18*j)+1] = radius * sin(prevyAng) *sin(prevAngUpper);
            mouth_vertex_buffer_data[(18*10*i)+(18*j)+2] = radius * cos(prevyAng);

            mouth_vertex_buffer_data[(18*10*i)+(18*j)+3] = radius * sin(yAng) *cos(ang);
            mouth_vertex_buffer_data[(18*10*i)+(18*j)+4] = radius * sin(yAng) *sin(ang);
            mouth_vertex_buffer_data[(18*10*i)+(18*j)+5] = radius * cos(yAng);

            mouth_vertex_buffer_data[(18*10*i)+(18*j)+6] = radius * sin(yAng) *cos(prevAng);
            mouth_vertex_buffer_data[(18*10*i)+(18*j)+7] = radius * sin(yAng) *sin(prevAng);
            mouth_vertex_buffer_data[(18*10*i)+(18*j)+8] = radius * cos(yAng);

            mouth_vertex_buffer_data[(18*10*i)+(18*j)+9] = radius * sin(prevyAng) *cos(prevAng);
            mouth_vertex_buffer_data[(18*10*i)+(18*j)+10] =radius * sin(prevyAng) *sin(prevAngUpper);
            mouth_vertex_buffer_data[(18*10*i)+(18*j)+11] = radius * cos(prevyAng);

            mouth_vertex_buffer_data[(18*10*i)+(18*j)+12] = radius * sin(prevyAng) *cos(ang);
            mouth_vertex_buffer_data[(18*10*i)+(18*j)+13] = radius * sin(prevyAng) *sin(angUpper);
            mouth_vertex_buffer_data[(18*10*i)+(18*j)+14] = radius * cos(prevyAng);

            mouth_vertex_buffer_data[(18*10*i)+(18*j)+15] = radius * sin(yAng) *cos(ang);
            mouth_vertex_buffer_data[(18*10*i)+(18*j)+16] = radius * sin(yAng) *sin(ang);
            mouth_vertex_buffer_data[(18*10*i)+(18*j)+17] = radius * cos(yAng);
        }

    }

    float bottomHeight = 1.75;
    float mastHeight = 2;

    for(int i=0; i<10; ++i) {
        double prevAng = (2*i*PI/10.0);
        double ang = (2*(i+1)*PI/10.0);
        thorn_vertex_buffer_data[(18*i)+0] = 0.4 * cos(prevAng);
        thorn_vertex_buffer_data[(18*i)+1] = 0.4 * sin(prevAng);
        thorn_vertex_buffer_data[(18*i)+2] = bottomHeight;

        thorn_vertex_buffer_data[(18*i)+3] = 0 * 0.4 * cos(ang);
        thorn_vertex_buffer_data[(18*i)+4] = 0 * 0.4 * sin(ang);
        thorn_vertex_buffer_data[(18*i)+5] = bottomHeight + mastHeight;

        thorn_vertex_buffer_data[(18*i)+6] = 0 * 0.4 * cos(prevAng);
        thorn_vertex_buffer_data[(18*i)+7] = 0 * 0.4 * sin(prevAng);
        thorn_vertex_buffer_data[(18*i)+8] = bottomHeight + mastHeight;

        thorn_vertex_buffer_data[(18*i)+9] = 0.4 * cos(prevAng);
        thorn_vertex_buffer_data[(18*i)+10] = 0.4 * sin(prevAng);
        thorn_vertex_buffer_data[(18*i)+11] = bottomHeight;

        thorn_vertex_buffer_data[(18*i)+12] = 0.4 * cos(ang);
        thorn_vertex_buffer_data[(18*i)+13] = 0.4 * sin(ang);
        thorn_vertex_buffer_data[(18*i)+14] = bottomHeight;

        thorn_vertex_buffer_data[(18*i)+15] = 0 * 0.4 * cos(ang);
        thorn_vertex_buffer_data[(18*i)+16] = 0 * 0.4 * sin(ang);
        thorn_vertex_buffer_data[(18*i)+17] = bottomHeight + mastHeight;

        thorn_vertex_buffer_data[(18*10)+(18*i)+0] = 0 * 0;
        thorn_vertex_buffer_data[(18*10)+(18*i)+1] = 0 * 0;
        thorn_vertex_buffer_data[(18*10)+(18*i)+2] = bottomHeight + mastHeight;

        thorn_vertex_buffer_data[(18*10)+(18*i)+3] = 0 * 0.4 * cos(ang);
        thorn_vertex_buffer_data[(18*10)+(18*i)+4] = 0 * 0.4 * sin(ang);
        thorn_vertex_buffer_data[(18*10)+(18*i)+5] = bottomHeight + mastHeight;

        thorn_vertex_buffer_data[(18*10)+(18*i)+6] = 0 * 0.4 * cos(prevAng);
        thorn_vertex_buffer_data[(18*10)+(18*i)+7] = 0 * 0.4 * sin(prevAng);
        thorn_vertex_buffer_data[(18*10)+(18*i)+8] = bottomHeight + mastHeight;

        thorn_vertex_buffer_data[(18*10)+(18*i)+9] = 0;
        thorn_vertex_buffer_data[(18*10)+(18*i)+10] = 0;
        thorn_vertex_buffer_data[(18*10)+(18*i)+11] = bottomHeight;

        thorn_vertex_buffer_data[(18*10)+(18*i)+12] = 0.4 * cos(ang);
        thorn_vertex_buffer_data[(18*10)+(18*i)+13] = 0.4 * sin(ang);
        thorn_vertex_buffer_data[(18*10)+(18*i)+14] = bottomHeight;

        thorn_vertex_buffer_data[(18*10)+(18*i)+15] = 0.4 * cos(prevAng);
        thorn_vertex_buffer_data[(18*10)+(18*i)+16] = 0.4 * sin(prevAng);
        thorn_vertex_buffer_data[(18*10)+(18*i)+17] = bottomHeight;
    }

    for(int i=0; i<10; ++i) {
        double prevAng = (2*i*PI/10.0);
        double ang = (2*(i+1)*PI/10.0);
        cannon_vertex_buffer_data[(18*i)+0] = 1.3;
        cannon_vertex_buffer_data[(18*i)+1] = 0.3*sin(prevAng);
        cannon_vertex_buffer_data[(18*i)+2] = 1 + 0.3*cos(prevAng);

        cannon_vertex_buffer_data[(18*i)+3] = 0;
        cannon_vertex_buffer_data[(18*i)+4] = 0.3*sin(ang);
        cannon_vertex_buffer_data[(18*i)+5] = 1 + 0.3*cos(ang);

        cannon_vertex_buffer_data[(18*i)+6] = 0;
        cannon_vertex_buffer_data[(18*i)+7] = 0.3*sin(prevAng);
        cannon_vertex_buffer_data[(18*i)+8] = 1 + 0.3*cos(prevAng);

        cannon_vertex_buffer_data[(18*i)+9] =  1.3;
        cannon_vertex_buffer_data[(18*i)+10] = 0.3*sin(prevAng);
        cannon_vertex_buffer_data[(18*i)+11] =1 + 0.3*cos(prevAng);

        cannon_vertex_buffer_data[(18*i)+12] = 1.3;
        cannon_vertex_buffer_data[(18*i)+13] = 0.3*sin(ang);
        cannon_vertex_buffer_data[(18*i)+14] = 1 + 0.3*cos(ang);

        cannon_vertex_buffer_data[(18*i)+15] = 0;
        cannon_vertex_buffer_data[(18*i)+16] = 0.3*sin(ang);
        cannon_vertex_buffer_data[(18*i)+17] = 1 + 0.3*cos(ang);

        cannon_vertex_buffer_data[(18*10)+(18*i)+0] = 0;
        cannon_vertex_buffer_data[(18*10)+(18*i)+1] = 0;
        cannon_vertex_buffer_data[(18*10)+(18*i)+2] = 1;

        cannon_vertex_buffer_data[(18*10)+(18*i)+3] = 0;
        cannon_vertex_buffer_data[(18*10)+(18*i)+4] = 0.3*sin(ang);
        cannon_vertex_buffer_data[(18*10)+(18*i)+5] = 1 + 0.3*cos(ang);

        cannon_vertex_buffer_data[(18*10)+(18*i)+6] = 0;
        cannon_vertex_buffer_data[(18*10)+(18*i)+7] = 0.3*sin(prevAng);
        cannon_vertex_buffer_data[(18*10)+(18*i)+8] = 1 + 0.3*cos(prevAng);

        cannon_vertex_buffer_data[(18*10)+(18*i)+9] = 1.3;
        cannon_vertex_buffer_data[(18*10)+(18*i)+10] = 0;
        cannon_vertex_buffer_data[(18*10)+(18*i)+11] = 1;

        cannon_vertex_buffer_data[(18*10)+(18*i)+12] = 1.3;
        cannon_vertex_buffer_data[(18*10)+(18*i)+13] = 0.3*sin(ang);
        cannon_vertex_buffer_data[(18*10)+(18*i)+14] = 1 + 0.3*cos(ang);

        cannon_vertex_buffer_data[(18*10)+(18*i)+15] = 1.3;
        cannon_vertex_buffer_data[(18*10)+(18*i)+16] = 0.3*sin(prevAng);
        cannon_vertex_buffer_data[(18*10)+(18*i)+17] = 1 + 0.3*cos(prevAng);
    }

    this->object = create3DObject(GL_TRIANGLES, (sizeof(vertex_buffer_data)/(3*sizeof(vertex_buffer_data[0]))), vertex_buffer_data, color_t{74, 20, 140}, GL_FILL);
    this->thornObject = create3DObject(GL_TRIANGLES, (sizeof(thorn_vertex_buffer_data)/(3*sizeof(thorn_vertex_buffer_data[0]))), thorn_vertex_buffer_data, color_t{176, 190, 197}, GL_FILL);
    this->legObject = create3DObject(GL_TRIANGLES, (sizeof(leg_vertex_buffer_data)/(3*sizeof(leg_vertex_buffer_data[0]))), leg_vertex_buffer_data, color_t{233, 30, 99}, GL_FILL);
    this->eyeObject = create3DObject(GL_TRIANGLES, (sizeof(cannon_vertex_buffer_data)/(3*sizeof(cannon_vertex_buffer_data[0]))), cannon_vertex_buffer_data, color_t{255, 255, 255}, GL_FILL);
    this->mouthObject = create3DObject(GL_TRIANGLES, (sizeof(mouth_vertex_buffer_data)/(3*sizeof(mouth_vertex_buffer_data[0]))), mouth_vertex_buffer_data, color_t{240, 98, 146}, GL_FILL);
    this->shape = sphereBounding(this->position.x, this->position.y, this->position.z, 3.0f);
}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, 0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->thornObject);
    draw3DObject(this->legObject);
    draw3DObject(this->object);
    draw3DObject(this->mouthObject);
    Matrices.model *= glm::translate (glm::vec3(0, -0.7, 0));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->eyeObject);
    Matrices.model *= glm::translate (glm::vec3(0, 2 * 0.7, 0));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->eyeObject);
}

