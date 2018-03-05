#include "boat.h"
#include "main.h"
#include "texture.h"

Boat::Boat(float x, float y, color_t color, color_t baseColor) {
    speed = -0.025f;
    this->position = glm::vec3(x, y, 2*speed);
    this->rotation = 0;
    this->velocity = 0;
    this->upVelocity = -1;
    GLfloat vertex_buffer_data[9*2*10*11];
    GLfloat base_vertex_buffer_data[9*2*2*10];
    GLfloat sail_vertex_buffer_data[9*2*10*1];
    GLfloat mast_vertex_buffer_data[9*2*2*11];
    GLfloat g_uv_buffer_data[6*2*2*11];
    double bentSine[11];
    this->Texture = loadDDS("dragon.dds");

    for(int i=0; i<=10; ++i) {
        double ang = 0.8+((i/10.0)*(PI-0.8));
        bentSine[10-i] = sin(ang)+0*2*atan(sin(ang)/(2.0 - cos(ang)));
    }

    for(int i=0; i<10; ++i) {
        float prevyCord = ((i-5)/10.0);
        float yCord = ((i-4)/10.0);

        for(int j=0; j<10; ++j) {
            float prevxCord = (j-5);
            float xCord = (j-4);

            vertex_buffer_data[(18*11*i)+(18*j)+0] = prevxCord;
            vertex_buffer_data[(18*11*i)+(18*j)+1] = 3.5*bentSine[j]*(prevyCord);
            vertex_buffer_data[(18*11*i)+(18*j)+2] = 8 * prevyCord * prevyCord;

            vertex_buffer_data[(18*11*i)+(18*j)+3] = xCord;
            vertex_buffer_data[(18*11*i)+(18*j)+4] = 3.5*bentSine[j+1]*(yCord);
            vertex_buffer_data[(18*11*i)+(18*j)+5] = 8 * yCord * yCord;

            vertex_buffer_data[(18*11*i)+(18*j)+6] = prevxCord;
            vertex_buffer_data[(18*11*i)+(18*j)+7] = 3.5*bentSine[j]*(yCord);
            vertex_buffer_data[(18*11*i)+(18*j)+8] = 8 * yCord * yCord;

            vertex_buffer_data[(18*11*i)+(18*j)+9] = prevxCord;
            vertex_buffer_data[(18*11*i)+(18*j)+10] = 3.5*bentSine[j]*(prevyCord);
            vertex_buffer_data[(18*11*i)+(18*j)+11] = 8 * prevyCord * prevyCord;

            vertex_buffer_data[(18*11*i)+(18*j)+12] = xCord;
            vertex_buffer_data[(18*11*i)+(18*j)+13] = 3.5*bentSine[j+1]*(prevyCord);
            vertex_buffer_data[(18*11*i)+(18*j)+14] = 8 * prevyCord * prevyCord;

            vertex_buffer_data[(18*11*i)+(18*j)+15] = xCord;
            vertex_buffer_data[(18*11*i)+(18*j)+16] = 3.5*bentSine[j+1]*(yCord);
            vertex_buffer_data[(18*11*i)+(18*j)+17] = 8 * yCord * yCord;

            if( abs(i-4) == 3) {
                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+0] = prevxCord;
                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+1] = 3.5*bentSine[j]*(yCord);
                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+2] = 8 * yCord * yCord;

                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+3] = xCord;
                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+4] = 0;
                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+5] = 8 * yCord * yCord;

                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+6] = xCord;
                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+7] = 3.5*bentSine[j+1]*(yCord);
                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+8] = 8 * yCord * yCord;

                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+9] = prevxCord;
                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+10] = 3.5*bentSine[j]*(yCord);
                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+11] = 8 * yCord * yCord;

                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+12] = prevxCord;
                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+13] = 0;
                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+14] = 8 * yCord * yCord;

                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+15] = xCord;
                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+16] = 0;
                base_vertex_buffer_data[(18*10*(yCord>0))+(18*j)+17] = 8 * yCord * yCord;
            }
        }

        vertex_buffer_data[(18*11*i)+(180)+0] = 5;
        vertex_buffer_data[(18*11*i)+(180)+1] = 3.5*bentSine[10]*(prevyCord);
        vertex_buffer_data[(18*11*i)+(180)+2] = 8 * prevyCord * prevyCord;

        vertex_buffer_data[(18*11*i)+(180)+3] = 5;
        vertex_buffer_data[(18*11*i)+(180)+4] = 0;
        vertex_buffer_data[(18*11*i)+(180)+5] = 8 * yCord * yCord;

        vertex_buffer_data[(18*11*i)+(180)+6] = 5;
        vertex_buffer_data[(18*11*i)+(180)+7] = 3.5*bentSine[10]*(yCord);
        vertex_buffer_data[(18*11*i)+(180)+8] = 8 * yCord * yCord;

        vertex_buffer_data[(18*11*i)+(180)+9] = 5;
        vertex_buffer_data[(18*11*i)+(180)+10] = 3.5*bentSine[10]*(prevyCord);
        vertex_buffer_data[(18*11*i)+(180)+11] = 8 * prevyCord * prevyCord;

        vertex_buffer_data[(18*11*i)+(180)+12] = 5;
        vertex_buffer_data[(18*11*i)+(180)+13] = 0;
        vertex_buffer_data[(18*11*i)+(180)+14] = 8 * prevyCord * prevyCord;

        vertex_buffer_data[(18*11*i)+(180)+15] = 5;
        vertex_buffer_data[(18*11*i)+(180)+16] = 0;
        vertex_buffer_data[(18*11*i)+(180)+17] = 8 * yCord * yCord;
    }

    int mastHeight = 8;

    for(int i=0; i<10; ++i) {
        double prevAng = (2*i*PI/10.0);
        double ang = (2*(i+1)*PI/10.0);
        mast_vertex_buffer_data[(18*i)+0] = 0.1*cos(prevAng);
        mast_vertex_buffer_data[(18*i)+1] = 0.1*sin(prevAng);
        mast_vertex_buffer_data[(18*i)+2] = 0;

        mast_vertex_buffer_data[(18*i)+3] = 0.1*cos(ang);
        mast_vertex_buffer_data[(18*i)+4] = 0.1*sin(ang);
        mast_vertex_buffer_data[(18*i)+5] = mastHeight;

        mast_vertex_buffer_data[(18*i)+6] = 0.1*cos(prevAng);
        mast_vertex_buffer_data[(18*i)+7] = 0.1*sin(prevAng);
        mast_vertex_buffer_data[(18*i)+8] = mastHeight;

        mast_vertex_buffer_data[(18*i)+9] = 0.1*cos(prevAng);
        mast_vertex_buffer_data[(18*i)+10] = 0.1*sin(prevAng);
        mast_vertex_buffer_data[(18*i)+11] = 0;

        mast_vertex_buffer_data[(18*i)+12] = 0.1*cos(ang);
        mast_vertex_buffer_data[(18*i)+13] = 0.1*sin(ang);
        mast_vertex_buffer_data[(18*i)+14] = 0;

        mast_vertex_buffer_data[(18*i)+15] = 0.1*cos(ang);
        mast_vertex_buffer_data[(18*i)+16] = 0.1*sin(ang);
        mast_vertex_buffer_data[(18*i)+17] = mastHeight;

        mast_vertex_buffer_data[(18*10)+(18*i)+0] = 0;
        mast_vertex_buffer_data[(18*10)+(18*i)+1] = 0;
        mast_vertex_buffer_data[(18*10)+(18*i)+2] = mastHeight;

        mast_vertex_buffer_data[(18*10)+(18*i)+3] = 0.1*cos(ang);
        mast_vertex_buffer_data[(18*10)+(18*i)+4] = 0.1*sin(ang);
        mast_vertex_buffer_data[(18*10)+(18*i)+5] = mastHeight;

        mast_vertex_buffer_data[(18*10)+(18*i)+6] = 0.1*cos(prevAng);
        mast_vertex_buffer_data[(18*10)+(18*i)+7] = 0.1*sin(prevAng);
        mast_vertex_buffer_data[(18*10)+(18*i)+8] = mastHeight;

        mast_vertex_buffer_data[(18*10)+(18*i)+9] = 0;
        mast_vertex_buffer_data[(18*10)+(18*i)+10] = 0;
        mast_vertex_buffer_data[(18*10)+(18*i)+11] = 0;

        mast_vertex_buffer_data[(18*10)+(18*i)+12] = 0.1*cos(ang);
        mast_vertex_buffer_data[(18*10)+(18*i)+13] = 0.1*sin(ang);
        mast_vertex_buffer_data[(18*10)+(18*i)+14] = 0;

        mast_vertex_buffer_data[(18*10)+(18*i)+15] = 0.1*cos(prevAng);
        mast_vertex_buffer_data[(18*10)+(18*i)+16] = 0.1*sin(prevAng);
        mast_vertex_buffer_data[(18*10)+(18*i)+17] = 0;
    }

    for(int i=0; i<10; ++i) {
        double prevyCord = (i)/2.0;
        double yCord = (i+1)/2.0;
        double prevAng = (i*PI/10.0);
        double ang = ((i+1)*PI/10.0);
        sail_vertex_buffer_data[(18*i)+0] = -sin(prevAng);
        sail_vertex_buffer_data[(18*i)+1] = prevyCord * 0.7;
        sail_vertex_buffer_data[(18*i)+2] = mastHeight - 0.7*(i/10.0*mastHeight);

        sail_vertex_buffer_data[(18*i)+3] = -sin(ang);
        sail_vertex_buffer_data[(18*i)+4] = -yCord * 0.7;
        sail_vertex_buffer_data[(18*i)+5] = mastHeight - 0.7*((i+1)/10.0*mastHeight);

        sail_vertex_buffer_data[(18*i)+6] = -sin(ang);
        sail_vertex_buffer_data[(18*i)+7] = yCord * 0.7;
        sail_vertex_buffer_data[(18*i)+8] = mastHeight - 0.7*((i+1)/10.0*mastHeight);

        sail_vertex_buffer_data[(18*i)+9] = -sin(prevAng);
        sail_vertex_buffer_data[(18*i)+10] = prevyCord * 0.7;
        sail_vertex_buffer_data[(18*i)+11] = mastHeight - 0.7*((i)/10.0*mastHeight);

        sail_vertex_buffer_data[(18*i)+12] = -sin(prevAng);
        sail_vertex_buffer_data[(18*i)+13] = -prevyCord * 0.7;
        sail_vertex_buffer_data[(18*i)+14] = mastHeight - 0.7*((i)/10.0*mastHeight);

        sail_vertex_buffer_data[(18*i)+15] = -sin(ang);
        sail_vertex_buffer_data[(18*i)+16] = -yCord * 0.7;
        sail_vertex_buffer_data[(18*i)+17] = mastHeight - 0.7*((i+1)/10.0*mastHeight);

        g_uv_buffer_data[(12*i)+0] = 2;
        g_uv_buffer_data[(12*i)+1] = 2 * (1.0 - i/10.0);

        g_uv_buffer_data[(12*i)+2] = 0;
        g_uv_buffer_data[(12*i)+3] = 2 * (1.0 - (i+1)/10.0);

        g_uv_buffer_data[(12*i)+4] = 2;
        g_uv_buffer_data[(12*i)+5] = 2 * (1.0 - (i+1)/10.0);

        g_uv_buffer_data[(12*i)+6] = 2;
        g_uv_buffer_data[(12*i)+7] = 2 * (1.0 - i/10.0);

        g_uv_buffer_data[(12*i)+8] = 0;
        g_uv_buffer_data[(12*i)+9] = 2 * (1.0 - i/10.0);

        g_uv_buffer_data[(12*i)+10] = 0;
        g_uv_buffer_data[(12*i)+11] = 2 * (1.0 - (i+1)/10.0);
    }

    this->object = create3DObject(GL_TRIANGLES, (sizeof(vertex_buffer_data)/(3*sizeof(vertex_buffer_data[0]))), vertex_buffer_data, color, GL_FILL);
    this->mastObject = create3DObject(GL_TRIANGLES, (sizeof(mast_vertex_buffer_data)/(3*sizeof(mast_vertex_buffer_data[0]))), mast_vertex_buffer_data, color, GL_FILL);
    this->baseObject = create3DObject(GL_TRIANGLES, (sizeof(base_vertex_buffer_data)/(3*sizeof(base_vertex_buffer_data[0]))), base_vertex_buffer_data, baseColor, GL_FILL);
    this->sailObject = createTextured3DObject(GL_TRIANGLES, (sizeof(sail_vertex_buffer_data)/(3*sizeof(sail_vertex_buffer_data[0]))), sail_vertex_buffer_data, g_uv_buffer_data, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->mastObject);
    draw3DObject(this->baseObject);
}

void Boat::texturedDraw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(textureMatrixID, 1, GL_FALSE, &MVP[0][0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->Texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);
    draw3DObject(this->sailObject, 1);
}

void Boat::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boat::tick() {
    this->position.x -= velocity * cos(this->rotation * PI / 180.0f);
    this->position.y -= velocity * sin(this->rotation * PI / 180.0f);
    if(this->velocity > 0) {
        this->velocity = std::max(0.0, this->velocity - 0.004);
    }
    else if(this->velocity < 0) {
        this->velocity = std::min(0.0, this->velocity + 0.004);
    }
    if(this->upVelocity >= 0 or this->position.z > 0) {
        this->position.z += this->upVelocity;
        this->upVelocity -= 0.02;
        this->position.z = std::max(this->position.z, -0.48f);
    }
    else {
        if(this->position.z < -0.5 or this->position.z >= -0.03) speed = -speed;
        this->position.z -= speed;
    }
}

