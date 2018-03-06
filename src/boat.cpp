#include "boat.h"
#include "main.h"
#include "texture.h"

Boat::Boat(float x, float y, color_t color, color_t baseColor, color_t arrowColor) {
    speed = -0.025f;
    this->position = glm::vec3(x, y, 2*speed);
    this->rotation = 0;
    this->windRatio = 0;
    this->mastRatio = 0;
    this->oldWindAngle = 0;
    this->velocity = 0;
    this->upVelocity = -1;
    this->windAngle = 0;
    this->oldMastScale = 1;
    this->mastScale = 1;
    this->cannonRotation = 0;
    GLfloat vertex_buffer_data[9*2*10*11];
    GLfloat base_vertex_buffer_data[9*2*2*10];
    GLfloat sail_vertex_buffer_data[9*2*10*1];
    GLfloat g_uv_buffer_data[6*2*10*1];
    GLfloat mast_vertex_buffer_data[9*2*2*10];
    GLfloat arrow_vertex_buffer_data[9*3];
    GLfloat cannon_vertex_buffer_data[9*2*2*10];
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
        g_uv_buffer_data[(12*i)+1] = 2 * (i/10.0);

        g_uv_buffer_data[(12*i)+2] = 0;
        g_uv_buffer_data[(12*i)+3] = 2 * ((i+1)/10.0);

        g_uv_buffer_data[(12*i)+4] = 2;
        g_uv_buffer_data[(12*i)+5] = 2 * ((i+1)/10.0);

        g_uv_buffer_data[(12*i)+6] = 2;
        g_uv_buffer_data[(12*i)+7] = 2 * (i/10.0);

        g_uv_buffer_data[(12*i)+8] = 0;
        g_uv_buffer_data[(12*i)+9] = 2 * (i/10.0);

        g_uv_buffer_data[(12*i)+10] = 0;
        g_uv_buffer_data[(12*i)+11] = 2 * ((i+1)/10.0);
    }

    float arrowWidth = 0.25;

    arrow_vertex_buffer_data[0] = 7;
    arrow_vertex_buffer_data[1] = -2 * arrowWidth;
    arrow_vertex_buffer_data[2] = 1;

    arrow_vertex_buffer_data[3] = 6;
    arrow_vertex_buffer_data[4] = 0;
    arrow_vertex_buffer_data[5] = 1;

    arrow_vertex_buffer_data[6] = 7;
    arrow_vertex_buffer_data[7] = 2 * arrowWidth;
    arrow_vertex_buffer_data[8] = 1;

    arrow_vertex_buffer_data[9+0] = 7;
    arrow_vertex_buffer_data[9+1] = -arrowWidth;
    arrow_vertex_buffer_data[9+2] = 1;

    arrow_vertex_buffer_data[9+3] = 8.5;
    arrow_vertex_buffer_data[9+4] = arrowWidth;
    arrow_vertex_buffer_data[9+5] = 1;

    arrow_vertex_buffer_data[9+6] = 8.5;
    arrow_vertex_buffer_data[9+7] = -arrowWidth;
    arrow_vertex_buffer_data[9+8] = 1;

    arrow_vertex_buffer_data[18+0] = 7;
    arrow_vertex_buffer_data[18+1] = -arrowWidth;
    arrow_vertex_buffer_data[18+2] = 1;

    arrow_vertex_buffer_data[18+3] = 7;
    arrow_vertex_buffer_data[18+4] = arrowWidth;
    arrow_vertex_buffer_data[18+5] = 1;

    arrow_vertex_buffer_data[18+6] = 8.5;
    arrow_vertex_buffer_data[18+7] = arrowWidth;
    arrow_vertex_buffer_data[18+8] = 1;

    for(int i=0; i<10; ++i) {
        double prevAng = (2*i*PI/10.0);
        double ang = (2*(i+1)*PI/10.0);
        cannon_vertex_buffer_data[(18*i)+0] = -6.5;
        cannon_vertex_buffer_data[(18*i)+1] = 0.3*sin(prevAng);
        cannon_vertex_buffer_data[(18*i)+2] = 2 + 0.3*cos(prevAng);

        cannon_vertex_buffer_data[(18*i)+3] = -3.5;
        cannon_vertex_buffer_data[(18*i)+4] = 0.3*sin(ang);
        cannon_vertex_buffer_data[(18*i)+5] = 2 + 0.3*cos(ang);

        cannon_vertex_buffer_data[(18*i)+6] = -3.5;
        cannon_vertex_buffer_data[(18*i)+7] = 0.3*sin(prevAng);
        cannon_vertex_buffer_data[(18*i)+8] = 2 + 0.3*cos(prevAng);

        cannon_vertex_buffer_data[(18*i)+9] =  -6.5;
        cannon_vertex_buffer_data[(18*i)+10] = 0.3*sin(prevAng);
        cannon_vertex_buffer_data[(18*i)+11] =2 + 0.3*cos(prevAng);

        cannon_vertex_buffer_data[(18*i)+12] = -6.5;
        cannon_vertex_buffer_data[(18*i)+13] = 0.3*sin(ang);
        cannon_vertex_buffer_data[(18*i)+14] = 2 + 0.3*cos(ang);

        cannon_vertex_buffer_data[(18*i)+15] = -3.5;
        cannon_vertex_buffer_data[(18*i)+16] = 0.3*sin(ang);
        cannon_vertex_buffer_data[(18*i)+17] = 2 + 0.3*cos(ang);

        cannon_vertex_buffer_data[(18*10)+(18*i)+0] = -3.5;
        cannon_vertex_buffer_data[(18*10)+(18*i)+1] = 0;
        cannon_vertex_buffer_data[(18*10)+(18*i)+2] = 2;

        cannon_vertex_buffer_data[(18*10)+(18*i)+3] = -3.5;
        cannon_vertex_buffer_data[(18*10)+(18*i)+4] = 0.3*sin(ang);
        cannon_vertex_buffer_data[(18*10)+(18*i)+5] = 2 + 0.3*cos(ang);

        cannon_vertex_buffer_data[(18*10)+(18*i)+6] = -3.5;
        cannon_vertex_buffer_data[(18*10)+(18*i)+7] = 0.3*sin(prevAng);
        cannon_vertex_buffer_data[(18*10)+(18*i)+8] = 2 + 0.3*cos(prevAng);

        cannon_vertex_buffer_data[(18*10)+(18*i)+9] = -6.5;
        cannon_vertex_buffer_data[(18*10)+(18*i)+10] = 0;
        cannon_vertex_buffer_data[(18*10)+(18*i)+11] = 2;

        cannon_vertex_buffer_data[(18*10)+(18*i)+12] = -6.5;
        cannon_vertex_buffer_data[(18*10)+(18*i)+13] = 0.3*sin(ang);
        cannon_vertex_buffer_data[(18*10)+(18*i)+14] = 2 + 0.3*cos(ang);

        cannon_vertex_buffer_data[(18*10)+(18*i)+15] = -6.5;
        cannon_vertex_buffer_data[(18*10)+(18*i)+16] = 0.3*sin(prevAng);
        cannon_vertex_buffer_data[(18*10)+(18*i)+17] = 2 + 0.3*cos(prevAng);
    }

    this->object = create3DObject(GL_TRIANGLES, (sizeof(vertex_buffer_data)/(3*sizeof(vertex_buffer_data[0]))), vertex_buffer_data, color, GL_FILL);
    this->mastObject = create3DObject(GL_TRIANGLES, (sizeof(mast_vertex_buffer_data)/(3*sizeof(mast_vertex_buffer_data[0]))), mast_vertex_buffer_data, color, GL_FILL);
    this->baseObject = create3DObject(GL_TRIANGLES, (sizeof(base_vertex_buffer_data)/(3*sizeof(base_vertex_buffer_data[0]))), base_vertex_buffer_data, baseColor, GL_FILL);
    this->sailObject = createTextured3DObject(GL_TRIANGLES, (sizeof(sail_vertex_buffer_data)/(3*sizeof(sail_vertex_buffer_data[0]))), sail_vertex_buffer_data, g_uv_buffer_data, GL_FILL);
    this->arrowObject = create3DObject(GL_TRIANGLES, (sizeof(arrow_vertex_buffer_data)/(3*sizeof(arrow_vertex_buffer_data[0]))), arrow_vertex_buffer_data, arrowColor, GL_FILL);
    this->cannonObject = create3DObject(GL_TRIANGLES, (sizeof(cannon_vertex_buffer_data)/(3*sizeof(cannon_vertex_buffer_data[0]))), cannon_vertex_buffer_data, color_t{0,0,0}, GL_FILL);

    for(int i=0; i<(sizeof(base_vertex_buffer_data)/sizeof(base_vertex_buffer_data[0])); i+=3) {
        this->shape.origPoints.push_back(glm::vec3(base_vertex_buffer_data[i], base_vertex_buffer_data[i+1], base_vertex_buffer_data[i+2]));
    }
    this->sphereShape = sphereBounding(this->position.x, this->position.y, this->position.z, 4.5f);
    this->humanShape = sphereBounding(this->position.x, this->position.y, this->position.z + 2.0f, 1.0f);

    float length = 0.4f, breadth = 0.6f, depth = 0.6f, bottomHeight = 4;
    static GLfloat face_vertex_buffer_data[] = {
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f, -breadth, depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight
    };

    length = 0.55f, breadth = 0.8f, depth = 0.8f, bottomHeight = 2.7;
    static GLfloat shirt_vertex_buffer_data[] = {
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f, -breadth, depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight
    };
    length = 0.25f, breadth = 0.25f, depth = 0.8f, bottomHeight = 1.9;
    static GLfloat hand_vertex_buffer_data[] = {
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f, -breadth, depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight
    };

    length = 0.25f, breadth = 0.25f, depth = 0.6f, bottomHeight = 2.8;
    static GLfloat foot_vertex_buffer_data[] = {
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f, -breadth, depth + bottomHeight,
        -length + 2.5f, -breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f, -breadth, depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f, -breadth,-depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f,  breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f,  breadth,-depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f,  breadth, depth + bottomHeight,
        -length + 2.5f,  breadth, depth + bottomHeight,
        length + 2.5f, -breadth, depth + bottomHeight
    };

    this->faceObject = create3DObject(GL_TRIANGLES, 12*3, face_vertex_buffer_data, color_t{255,205,148}, GL_FILL);
    this->shirtObject = create3DObject(GL_TRIANGLES, 12*3, shirt_vertex_buffer_data, color_t{255, 53, 53}, GL_FILL);
    this->handObject = create3DObject(GL_TRIANGLES, 12*3, hand_vertex_buffer_data, color_t{255,205,148}, GL_FILL);
    this->footObject = create3DObject(GL_TRIANGLES, 12*3, foot_vertex_buffer_data, color_t{255,205,148}, GL_FILL);
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
    draw3DObject(this->baseObject);
    glm::mat4 arrowTranslate = glm::translate (glm::vec3(-7, 0, 0));
    glm::mat4 arrowRotate    = glm::rotate((float) ((this->windAngle-this->rotation) * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 arrowTranslateinv = glm::translate (glm::vec3(7, 0, 0));
    Matrices.model *= (arrowTranslateinv * arrowRotate * arrowTranslate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->arrowObject);
    Matrices.model = glm::mat4(1.0f);
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->mastObject);
    glm::mat4 cannonTranslate = glm::translate (glm::vec3(2.8, 0, 0));
    glm::mat4 cannonRotate    = glm::rotate((float) ((this->cannonRotation) * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 cannonTranslateinv = glm::translate (glm::vec3(-2.8, 0, 0));
    Matrices.model *= (cannonTranslateinv * cannonRotate * cannonTranslate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->cannonObject);
    draw3DObject(this->faceObject);
    draw3DObject(this->shirtObject);

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate * glm::translate(glm::vec3(0, -0.5, 0)));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->handObject);
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate * glm::translate(glm::vec3(0, 0.5, 0)));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->handObject);

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate * glm::translate(glm::vec3(0, -1, 0)));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->footObject);
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate * glm::translate(glm::vec3(0, 1, 0)));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->footObject);
}

void Boat::texturedDraw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (((this->windAngle * this->windRatio) + (this->oldWindAngle * (1.0 - this->windRatio))) * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    glm::mat4 scale = glm::scale(glm::vec3(((this->mastScale * this->mastRatio) + (this->oldMastScale * (1.0 - this->mastRatio))), ((this->mastScale * this->mastRatio) + (this->oldMastScale * (1.0 - this->mastRatio))), ((this->mastScale * this->mastRatio) + (this->oldMastScale * (1.0 - this->mastRatio)))));
    Matrices.model *= (translate * rotate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(textureMatrixID, 1, GL_FALSE, &MVP[0][0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->Texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);
    draw3DObject(this->sailObject, 1);
}

void Boat::islandDraw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * glm::translate(glm::vec3(-2.5, 0, 0)));
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->faceObject);
    draw3DObject(this->shirtObject);

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate * glm::translate(glm::vec3(-2.5, -0.5, 0)));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->handObject);
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate * glm::translate(glm::vec3(-2.5, 0.5, 0)));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->handObject);

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate * glm::translate(glm::vec3(-2.5, -1, 0)));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->footObject);
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate * glm::translate(glm::vec3(-2.5, 1, 0)));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->footObject);
}

void Boat::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boat::tick() {
    if(cos((this->windAngle - this->rotation)*PI/180.0) > 0.3) {
        this->position.x -= (1 + cos((this->windAngle - this->rotation)*PI/180.0)) * velocity * cos(this->rotation * PI / 180.0f);
        this->position.y -= (1 + cos((this->windAngle - this->rotation)*PI/180.0)) * velocity * sin(this->rotation * PI / 180.0f);
    }
    else {
        this->position.x -= velocity * cos(this->rotation * PI / 180.0f);
        this->position.y -= velocity * sin(this->rotation * PI / 180.0f);
    }
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
    this->windRatio = std::min(1.0f, this->windRatio + 0.01f);
    this->mastRatio = std::min(1.0f, this->mastRatio + 0.04f);

    this->shape.points.clear();
    for(auto&z: this->shape.origPoints) {
        glm::vec3 temp = z;
        temp = glm::rotate(temp, (this->rotation * PI / 180.0f), glm::vec3(0, 0, 1));
        temp += this->position;
        this->shape.points.emplace_back(temp);
    }
    this->sphereShape.position = this->position;
    this->humanShape.position = this->position;
}

void Boat::islandTick(sphereBounding shape2, int broken) {
    auto oldPosition = this->position;
    this->position.x -= velocity * cos(this->rotation * PI / 180.0f);
    this->position.y -= velocity * sin(this->rotation * PI / 180.0f);
    if(broken == 0 and 100-2 <= this->position.x and this->position.x <= 100+2 and 100-4 <= this->position.y and this->position.y <= 100+4) {
        this->position = oldPosition;
    }
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

    this->shape.points.clear();
    for(auto&z: this->shape.origPoints) {
        glm::vec3 temp = z;
        temp = glm::rotate(temp, (this->rotation * PI / 180.0f), glm::vec3(0, 0, 1));
        temp += this->position;
        this->shape.points.emplace_back(temp);
    }
    this->sphereShape.position = this->position;
    this->humanShape.position = this->position;
}