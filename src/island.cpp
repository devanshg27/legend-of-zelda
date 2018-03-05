#include "island.h"
#include "main.h"

Island::Island(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat mast_vertex_buffer_data[9*2*2*30];

    float mastHeight = 1.05;

    for(int i=0; i<30; ++i) {
        double prevAng = (2*i*PI/30.0);
        double ang = (2*(i+1)*PI/30.0);
        mast_vertex_buffer_data[(18*i)+0] = 30 * cos(prevAng);
        mast_vertex_buffer_data[(18*i)+1] = 30 * sin(prevAng);
        mast_vertex_buffer_data[(18*i)+2] = 0;

        mast_vertex_buffer_data[(18*i)+3] = 30 * cos(ang);
        mast_vertex_buffer_data[(18*i)+4] = 30 * sin(ang);
        mast_vertex_buffer_data[(18*i)+5] = mastHeight;

        mast_vertex_buffer_data[(18*i)+6] = 30 * cos(prevAng);
        mast_vertex_buffer_data[(18*i)+7] = 30 * sin(prevAng);
        mast_vertex_buffer_data[(18*i)+8] = mastHeight;

        mast_vertex_buffer_data[(18*i)+9] = 30 * cos(prevAng);
        mast_vertex_buffer_data[(18*i)+10] = 30 * sin(prevAng);
        mast_vertex_buffer_data[(18*i)+11] = 0;

        mast_vertex_buffer_data[(18*i)+12] = 30 * cos(ang);
        mast_vertex_buffer_data[(18*i)+13] = 30 * sin(ang);
        mast_vertex_buffer_data[(18*i)+14] = 0;

        mast_vertex_buffer_data[(18*i)+15] = 30 * cos(ang);
        mast_vertex_buffer_data[(18*i)+16] = 30 * sin(ang);
        mast_vertex_buffer_data[(18*i)+17] = mastHeight;

        mast_vertex_buffer_data[(18*30)+(18*i)+0] = 0;
        mast_vertex_buffer_data[(18*30)+(18*i)+1] = 0;
        mast_vertex_buffer_data[(18*30)+(18*i)+2] = mastHeight;

        mast_vertex_buffer_data[(18*30)+(18*i)+3] = 30 * cos(ang);
        mast_vertex_buffer_data[(18*30)+(18*i)+4] = 30 * sin(ang);
        mast_vertex_buffer_data[(18*30)+(18*i)+5] = mastHeight;

        mast_vertex_buffer_data[(18*30)+(18*i)+6] = 30 * cos(prevAng);
        mast_vertex_buffer_data[(18*30)+(18*i)+7] = 30 * sin(prevAng);
        mast_vertex_buffer_data[(18*30)+(18*i)+8] = mastHeight;

        mast_vertex_buffer_data[(18*30)+(18*i)+9] = 0;
        mast_vertex_buffer_data[(18*30)+(18*i)+10] = 0;
        mast_vertex_buffer_data[(18*30)+(18*i)+11] = 0;

        mast_vertex_buffer_data[(18*30)+(18*i)+12] = 30 * cos(ang);
        mast_vertex_buffer_data[(18*30)+(18*i)+13] = 30 * sin(ang);
        mast_vertex_buffer_data[(18*30)+(18*i)+14] = 0;

        mast_vertex_buffer_data[(18*30)+(18*i)+15] = 30 * cos(prevAng);
        mast_vertex_buffer_data[(18*30)+(18*i)+16] = 30 * sin(prevAng);
        mast_vertex_buffer_data[(18*30)+(18*i)+17] = 0;
    }

    this->object = create3DObject(GL_TRIANGLES, (sizeof(mast_vertex_buffer_data)/(3*sizeof(mast_vertex_buffer_data[0]))), mast_vertex_buffer_data, color, GL_FILL);
}

void Island::draw(glm::mat4 VP) {
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

