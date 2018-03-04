#include "main.h"
#include "timer.h"
#include "ball.h"
#include "boat.h"
#include "sea.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Boat boat1;
Sea sea1;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
bool lbutton_down = false;
float previous_x_position, previous_y_position;
int cameraView = 3;
// Camera View can take values:
// 0 = Boat View
// 1 = Top View
// 2 = Tower View
// 3 = Follow-cam View
// 4 = Helicopter-cam View

Timer t60(1.0 / 60);

const float PI = acos(-1);
glm::vec3 curEye, curTarget;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5, 0, 7);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 0, 1);

    if(cameraView == 0) {
        eye = boat1.position;
        eye.x -= 6*cos(PI * boat1.rotation / 180.0);
        eye.y -= 6*sin(PI * boat1.rotation / 180.0);
        eye.z += 2;
        target = eye;
        target.x -= 2*cos(PI * boat1.rotation / 180.0);
        target.y -= 2*sin(PI * boat1.rotation / 180.0);
    }
    else if(cameraView == 1) {
        target = boat1.position;
        eye = boat1.position;
        eye.z = 30;
        up.x = -cos(PI * boat1.rotation / 180.0);
        up.y = -sin(PI * boat1.rotation / 180.0);
        up.z = 0;
    }
    else if(cameraView == 2) {
        eye.x = 100;
        eye.y = 100;
        eye.z = 60;
        target = boat1.position;
        target.z = 2;
    }
    else if(cameraView == 3) {
        target = boat1.position;
        target.z = 2;
        eye = boat1.position;
        eye.x += 14*cos(PI * boat1.rotation / 180.0);
        eye.y += 14*sin(PI * boat1.rotation / 180.0);
        eye.z = 8;
        curEye = eye;
        curTarget = target;
    }
    else if(cameraView == 4) {
        eye = curEye;
        target = curTarget;
    }
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    sea1.draw(VP);
    boat1.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    if (up) {
        boat1.velocity = 0.35;
    }
    if (down) {
        boat1.velocity = -0.15;
    }
    if(left) {
        boat1.rotation += 0.8;
    }
    if(right) {
        boat1.rotation -= 0.8;
    }
    if(cameraView != 4) return;
    if(lbutton_down) {
        double x;
        double y;
        glfwGetCursorPos(window, &x, &y);
        if(x > previous_x_position) {
            glm::vec3 dir = curTarget - curEye;
            glm::vec3 temp = glm::cross(dir, glm::vec3(0, 0, 1));
            glm::vec3 normal = glm::cross(temp, dir);
            dir = glm::rotate(dir, -PI/180.0f, normal);
            curTarget = dir + curEye;
        }
        else if(x < previous_x_position){
            glm::vec3 dir = curTarget - curEye;
            glm::vec3 temp = glm::cross(dir, glm::vec3(0, 0, 1));
            glm::vec3 normal = glm::cross(temp, dir);
            dir = glm::rotate(dir, PI/180.0f, normal);
            curTarget = dir + curEye;
        }
        if(y > previous_y_position) {
            glm::vec3 dir = curTarget - curEye;
            glm::vec3 normal = glm::cross(dir, glm::vec3(0, 0, 1));
            dir = glm::rotate(dir, -PI/180.0f, normal);
            float ang = acos(glm::dot(dir, glm::vec3(0, 0, 1))/(glm::length(dir)));
            if(ang > 0.7 and ang < 3) {
                curTarget = dir + curEye;
            }
        }
        else if(y < previous_y_position){
            glm::vec3 dir = curTarget - curEye;
            glm::vec3 normal = glm::cross(dir, glm::vec3(0, 0, 1));
            dir = glm::rotate(dir, PI/180.0f, normal);
            float ang = acos(glm::dot(dir, glm::vec3(0, 0, 1))/(glm::length(dir)));
            if(ang > 0.7 and ang < 3) {
                curTarget = dir + curEye;
            }
        }
        previous_x_position = x;
        previous_y_position = y;
    }
}

void tick_elements() {
    ball1.tick();
    boat1.tick();
    sea1.tick();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(0, 0, COLOR_RED);
    boat1 = Boat(-15, 0, COLOR_BLACK);
    sea1 = Sea(0, 2, COLOR_BLUE);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void inputHandler(int key, int action) {
    if(key == GLFW_KEY_V) {
        if(action == GLFW_PRESS) {
            cameraView = (cameraView + 1) % 5;
        }
        else if(action == GLFW_RELEASE) {
            // Do something
        }
    }
    if(key == GLFW_KEY_SPACE) {
        if(action == GLFW_PRESS) {
            if(boat1.position.z < 0.01) {
                boat1.upVelocity = 0.5;
            }
        }
        else if(action == GLFW_RELEASE) {
            // Do something
        }
    }
}

void scrollHandler(double offset) {
    if(cameraView != 4) return;
    glm::vec3 dir;
    if(offset > 0) dir = curTarget - curEye;
    else if(offset < 0) dir = curEye - curTarget;
    else return;
    dir = dir/(10*sqrt((dir.x*dir.x)+(dir.y*dir.y)+(dir.z*dir.z)));
    curEye = dir + curEye;
    curTarget = dir + curTarget;
    curEye.z = std::max(1.0f, curEye.z);
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1600;
    int height = 900;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float near = 0.01;
    float far = 10000.0f;
    Matrices.projection = glm::perspective(PI/2, (float)16.0/9, near, far);
}
