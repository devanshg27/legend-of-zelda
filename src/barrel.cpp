#include "barrel.h"
#include "main.h"

Barrel::Barrel(float x, float y, color_t color, color_t color2) {
    this->position = glm::vec3(x, y, 0);
    this->speed = 0.025f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat mast_vertex_buffer_data[9*2*2*10];
    GLfloat diamond1_vertex_buffer_data[9*2*2*10];
    GLfloat diamond2_vertex_buffer_data[9*2*2*10];

    float mastHeight = 1.05;

    for(int i=0; i<10; ++i) {
        double prevAng = (2*i*PI/10.0);
        double ang = (2*(i+1)*PI/10.0);
        mast_vertex_buffer_data[(18*i)+0] = 1.6 * cos(prevAng);
        mast_vertex_buffer_data[(18*i)+1] = 1.6 * sin(prevAng);
        mast_vertex_buffer_data[(18*i)+2] = 0;

        mast_vertex_buffer_data[(18*i)+3] = 1.6 * cos(ang);
        mast_vertex_buffer_data[(18*i)+4] = 1.6 * sin(ang);
        mast_vertex_buffer_data[(18*i)+5] = mastHeight;

        mast_vertex_buffer_data[(18*i)+6] = 1.6 * cos(prevAng);
        mast_vertex_buffer_data[(18*i)+7] = 1.6 * sin(prevAng);
        mast_vertex_buffer_data[(18*i)+8] = mastHeight;

        mast_vertex_buffer_data[(18*i)+9] = 1.6 * cos(prevAng);
        mast_vertex_buffer_data[(18*i)+10] = 1.6 * sin(prevAng);
        mast_vertex_buffer_data[(18*i)+11] = 0;

        mast_vertex_buffer_data[(18*i)+12] = 1.6 * cos(ang);
        mast_vertex_buffer_data[(18*i)+13] = 1.6 * sin(ang);
        mast_vertex_buffer_data[(18*i)+14] = 0;

        mast_vertex_buffer_data[(18*i)+15] = 1.6 * cos(ang);
        mast_vertex_buffer_data[(18*i)+16] = 1.6 * sin(ang);
        mast_vertex_buffer_data[(18*i)+17] = mastHeight;

        mast_vertex_buffer_data[(18*10)+(18*i)+0] = 0;
        mast_vertex_buffer_data[(18*10)+(18*i)+1] = 0;
        mast_vertex_buffer_data[(18*10)+(18*i)+2] = mastHeight;

        mast_vertex_buffer_data[(18*10)+(18*i)+3] = 1.6 * cos(ang);
        mast_vertex_buffer_data[(18*10)+(18*i)+4] = 1.6 * sin(ang);
        mast_vertex_buffer_data[(18*10)+(18*i)+5] = mastHeight;

        mast_vertex_buffer_data[(18*10)+(18*i)+6] = 1.6 * cos(prevAng);
        mast_vertex_buffer_data[(18*10)+(18*i)+7] = 1.6 * sin(prevAng);
        mast_vertex_buffer_data[(18*10)+(18*i)+8] = mastHeight;

        mast_vertex_buffer_data[(18*10)+(18*i)+9] = 0;
        mast_vertex_buffer_data[(18*10)+(18*i)+10] = 0;
        mast_vertex_buffer_data[(18*10)+(18*i)+11] = 0;

        mast_vertex_buffer_data[(18*10)+(18*i)+12] = 1.6 * cos(ang);
        mast_vertex_buffer_data[(18*10)+(18*i)+13] = 1.6 * sin(ang);
        mast_vertex_buffer_data[(18*10)+(18*i)+14] = 0;

        mast_vertex_buffer_data[(18*10)+(18*i)+15] = 1.6 * cos(prevAng);
        mast_vertex_buffer_data[(18*10)+(18*i)+16] = 1.6 * sin(prevAng);
        mast_vertex_buffer_data[(18*10)+(18*i)+17] = 0;
    }

    float bottomHeight = 4;
    mastHeight = 2;

    for(int i=0; i<10; ++i) {
        double prevAng = (2*i*PI/10.0);
        double ang = (2*(i+1)*PI/10.0);
        diamond1_vertex_buffer_data[(18*i)+0] = 0 * cos(prevAng);
        diamond1_vertex_buffer_data[(18*i)+1] = 0 * sin(prevAng);
        diamond1_vertex_buffer_data[(18*i)+2] = bottomHeight;

        diamond1_vertex_buffer_data[(18*i)+3] = 1.6 * cos(ang);
        diamond1_vertex_buffer_data[(18*i)+4] = 1.6 * sin(ang);
        diamond1_vertex_buffer_data[(18*i)+5] = bottomHeight + mastHeight;

        diamond1_vertex_buffer_data[(18*i)+6] = 1.6 * cos(prevAng);
        diamond1_vertex_buffer_data[(18*i)+7] = 1.6 * sin(prevAng);
        diamond1_vertex_buffer_data[(18*i)+8] = bottomHeight + mastHeight;

        diamond1_vertex_buffer_data[(18*i)+9] = 0 * cos(prevAng);
        diamond1_vertex_buffer_data[(18*i)+10] = 0 * sin(prevAng);
        diamond1_vertex_buffer_data[(18*i)+11] = bottomHeight;

        diamond1_vertex_buffer_data[(18*i)+12] = 0 * cos(ang);
        diamond1_vertex_buffer_data[(18*i)+13] = 0 * sin(ang);
        diamond1_vertex_buffer_data[(18*i)+14] = bottomHeight;

        diamond1_vertex_buffer_data[(18*i)+15] = 1.6 * cos(ang);
        diamond1_vertex_buffer_data[(18*i)+16] = 1.6 * sin(ang);
        diamond1_vertex_buffer_data[(18*i)+17] = bottomHeight + mastHeight;

        diamond1_vertex_buffer_data[(18*10)+(18*i)+0] = 0;
        diamond1_vertex_buffer_data[(18*10)+(18*i)+1] = 0;
        diamond1_vertex_buffer_data[(18*10)+(18*i)+2] = bottomHeight + mastHeight;

        diamond1_vertex_buffer_data[(18*10)+(18*i)+3] = 1.6 * cos(ang);
        diamond1_vertex_buffer_data[(18*10)+(18*i)+4] = 1.6 * sin(ang);
        diamond1_vertex_buffer_data[(18*10)+(18*i)+5] = bottomHeight + mastHeight;

        diamond1_vertex_buffer_data[(18*10)+(18*i)+6] = 1.6 * cos(prevAng);
        diamond1_vertex_buffer_data[(18*10)+(18*i)+7] = 1.6 * sin(prevAng);
        diamond1_vertex_buffer_data[(18*10)+(18*i)+8] = bottomHeight + mastHeight;

        diamond1_vertex_buffer_data[(18*10)+(18*i)+9] = 0;
        diamond1_vertex_buffer_data[(18*10)+(18*i)+10] = 0;
        diamond1_vertex_buffer_data[(18*10)+(18*i)+11] = bottomHeight;

        diamond1_vertex_buffer_data[(18*10)+(18*i)+12] = 0 * cos(ang);
        diamond1_vertex_buffer_data[(18*10)+(18*i)+13] = 0 * sin(ang);
        diamond1_vertex_buffer_data[(18*10)+(18*i)+14] = bottomHeight;

        diamond1_vertex_buffer_data[(18*10)+(18*i)+15] = 0 * cos(prevAng);
        diamond1_vertex_buffer_data[(18*10)+(18*i)+16] = 0 * sin(prevAng);
        diamond1_vertex_buffer_data[(18*10)+(18*i)+17] = bottomHeight;
    }

    bottomHeight = 6;
    mastHeight = 0.75;

    for(int i=0; i<10; ++i) {
        double prevAng = (2*i*PI/10.0);
        double ang = (2*(i+1)*PI/10.0);
        diamond2_vertex_buffer_data[(18*i)+0] = 1.6 * cos(prevAng);
        diamond2_vertex_buffer_data[(18*i)+1] = 1.6 * sin(prevAng);
        diamond2_vertex_buffer_data[(18*i)+2] = bottomHeight;

        diamond2_vertex_buffer_data[(18*i)+3] = 0.5 * 1.6 * cos(ang);
        diamond2_vertex_buffer_data[(18*i)+4] = 0.5 * 1.6 * sin(ang);
        diamond2_vertex_buffer_data[(18*i)+5] = bottomHeight + mastHeight;

        diamond2_vertex_buffer_data[(18*i)+6] = 0.5 * 1.6 * cos(prevAng);
        diamond2_vertex_buffer_data[(18*i)+7] = 0.5 * 1.6 * sin(prevAng);
        diamond2_vertex_buffer_data[(18*i)+8] = bottomHeight + mastHeight;

        diamond2_vertex_buffer_data[(18*i)+9] = 1.6 * cos(prevAng);
        diamond2_vertex_buffer_data[(18*i)+10] = 1.6 * sin(prevAng);
        diamond2_vertex_buffer_data[(18*i)+11] = bottomHeight;

        diamond2_vertex_buffer_data[(18*i)+12] = 1.6 * cos(ang);
        diamond2_vertex_buffer_data[(18*i)+13] = 1.6 * sin(ang);
        diamond2_vertex_buffer_data[(18*i)+14] = bottomHeight;

        diamond2_vertex_buffer_data[(18*i)+15] = 0.5 * 1.6 * cos(ang);
        diamond2_vertex_buffer_data[(18*i)+16] = 0.5 * 1.6 * sin(ang);
        diamond2_vertex_buffer_data[(18*i)+17] = bottomHeight + mastHeight;

        diamond2_vertex_buffer_data[(18*10)+(18*i)+0] = 0.5 * 0;
        diamond2_vertex_buffer_data[(18*10)+(18*i)+1] = 0.5 * 0;
        diamond2_vertex_buffer_data[(18*10)+(18*i)+2] = bottomHeight + mastHeight;

        diamond2_vertex_buffer_data[(18*10)+(18*i)+3] = 0.5 * 1.6 * cos(ang);
        diamond2_vertex_buffer_data[(18*10)+(18*i)+4] = 0.5 * 1.6 * sin(ang);
        diamond2_vertex_buffer_data[(18*10)+(18*i)+5] = bottomHeight + mastHeight;

        diamond2_vertex_buffer_data[(18*10)+(18*i)+6] = 0.5 * 1.6 * cos(prevAng);
        diamond2_vertex_buffer_data[(18*10)+(18*i)+7] = 0.5 * 1.6 * sin(prevAng);
        diamond2_vertex_buffer_data[(18*10)+(18*i)+8] = bottomHeight + mastHeight;

        diamond2_vertex_buffer_data[(18*10)+(18*i)+9] = 0;
        diamond2_vertex_buffer_data[(18*10)+(18*i)+10] = 0;
        diamond2_vertex_buffer_data[(18*10)+(18*i)+11] = bottomHeight;

        diamond2_vertex_buffer_data[(18*10)+(18*i)+12] = 1.6 * cos(ang);
        diamond2_vertex_buffer_data[(18*10)+(18*i)+13] = 1.6 * sin(ang);
        diamond2_vertex_buffer_data[(18*10)+(18*i)+14] = bottomHeight;

        diamond2_vertex_buffer_data[(18*10)+(18*i)+15] = 1.6 * cos(prevAng);
        diamond2_vertex_buffer_data[(18*10)+(18*i)+16] = 1.6 * sin(prevAng);
        diamond2_vertex_buffer_data[(18*10)+(18*i)+17] = bottomHeight;
    }

    this->object = create3DObject(GL_TRIANGLES, (sizeof(mast_vertex_buffer_data)/(3*sizeof(mast_vertex_buffer_data[0]))), mast_vertex_buffer_data, color, GL_FILL);
    this->diamondObject1 = create3DObject(GL_TRIANGLES, (sizeof(diamond1_vertex_buffer_data)/(3*sizeof(diamond1_vertex_buffer_data[0]))), diamond1_vertex_buffer_data, color2, GL_FILL);
    this->diamondObject2 = create3DObject(GL_TRIANGLES, (sizeof(diamond2_vertex_buffer_data)/(3*sizeof(diamond2_vertex_buffer_data[0]))), diamond2_vertex_buffer_data, color2, GL_FILL);

    this->shape = sphereBounding(this->position.x, this->position.y, this->position.z, 1.2f);
    this->shape2 = sphereBounding(this->position.x, this->position.y, this->position.z + ((4.0+6.75)/2.0), ((6.75-4)/1.8));
}

void Barrel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->diamondObject1);
    draw3DObject(this->diamondObject2);
}

void Barrel::tick() {
    this->position.z += speed;
    if(this->position.z < -0.5 or this->position.z >= 0.03) speed = -speed;
}