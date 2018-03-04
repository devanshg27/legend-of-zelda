#include "sea.h"
#include "main.h"
#include "texture.h"

Sea::Sea(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    this->Texture = loadDDS("uvtemplate.DDS");
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1000.0f,-1000.0f,-0.0f,
        -1000.0f,-1000.0f, 0.0f,
        -1000.0f, 1000.0f, 0.0f,
        1000.0f, 1000.0f,-0.0f,
        -1000.0f,-1000.0f,-0.0f,
        -1000.0f, 1000.0f,-0.0f,
        1000.0f,-1000.0f, 0.0f,
        -1000.0f,-1000.0f,-0.0f,
        1000.0f,-1000.0f,-0.0f,
        1000.0f, 1000.0f,-0.0f,
        1000.0f,-1000.0f,-0.0f,
        -1000.0f,-1000.0f,-0.0f,
        -1000.0f,-1000.0f,-0.0f,
        -1000.0f, 1000.0f, 0.0f,
        -1000.0f, 1000.0f,-0.0f,
        1000.0f,-1000.0f, 0.0f,
        -1000.0f,-1000.0f, 0.0f,
        -1000.0f,-1000.0f,-0.0f,
        -1000.0f, 1000.0f, 0.0f,
        -1000.0f,-1000.0f, 0.0f,
        1000.0f,-1000.0f, 0.0f,
        1000.0f, 1000.0f, 0.0f,
        1000.0f,-1000.0f,-0.0f,
        1000.0f, 1000.0f,-0.0f,
        1000.0f,-1000.0f,-0.0f,
        1000.0f, 1000.0f, 0.0f,
        1000.0f,-1000.0f, 0.0f,
        1000.0f, 1000.0f, 0.0f,
        1000.0f, 1000.0f,-0.0f,
        -1000.0f, 1000.0f,-0.0f,
        1000.0f, 1000.0f, 0.0f,
        -1000.0f, 1000.0f,-0.0f,
        -1000.0f, 1000.0f, 0.0f,
        1000.0f, 1000.0f, 0.0f,
        -1000.0f, 1000.0f, 0.0f,
        1000.0f,-1000.0f, 0.0f
    };

    // Two UV coordinatesfor each vertex. They were created with Blender.
    static const GLfloat g_uv_buffer_data[] = {
        0.000059f, 1.0f-0.000004f,
        0.000103f, 1.0f-0.336048f,
        0.335973f, 1.0f-0.335903f,
        1.000023f, 1.0f-0.000013f,
        0.667979f, 1.0f-0.335851f,
        0.999958f, 1.0f-0.336064f,
        0.667979f, 1.0f-0.335851f,
        0.336024f, 1.0f-0.671877f,
        0.667969f, 1.0f-0.671889f,
        1.000023f, 1.0f-0.000013f,
        0.668104f, 1.0f-0.000013f,
        0.667979f, 1.0f-0.335851f,
        0.000059f, 1.0f-0.000004f,
        0.335973f, 1.0f-0.335903f,
        0.336098f, 1.0f-0.000071f,
        0.667979f, 1.0f-0.335851f,
        0.335973f, 1.0f-0.335903f,
        0.336024f, 1.0f-0.671877f,
        1.000004f, 1.0f-0.671847f,
        0.999958f, 1.0f-0.336064f,
        0.667979f, 1.0f-0.335851f,
        0.668104f, 1.0f-0.000013f,
        0.335973f, 1.0f-0.335903f,
        0.667979f, 1.0f-0.335851f,
        0.335973f, 1.0f-0.335903f,
        0.668104f, 1.0f-0.000013f,
        0.336098f, 1.0f-0.000071f,
        0.000103f, 1.0f-0.336048f,
        0.000004f, 1.0f-0.671870f,
        0.336024f, 1.0f-0.671877f,
        0.000103f, 1.0f-0.336048f,
        0.336024f, 1.0f-0.671877f,
        0.335973f, 1.0f-0.335903f,
        0.667969f, 1.0f-0.671889f,
        1.000004f, 1.0f-0.671847f,
        0.667979f, 1.0f-0.335851f
    };

    this->object = createTextured3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, g_uv_buffer_data, GL_FILL);
}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->Texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);
    draw3DObject(this->object, 1);
}

void Sea::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Sea::tick() {
    this->rotation = 0;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

