#include <sys/types.h>
#include <unistd.h>

#include "main.h"
#include "physics.h"
#include "timer.h"
#include "ball.h"
#include "boat.h"
#include "sea.h"
#include "chest.h"
#include "rock.h"
#include "island.h"
#include "barrel.h"
#include "health.h"
#include "monster.h"
#include "booster.h"
#include "audio.h"
#include "display.h"
#include "aim.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLuint     textureProgramID;
GLuint textureMatrixID;
GLFWwindow *window;
GLuint TextureID;

/**************************
* Customizable functions *
**************************/

char windowTitle[256];
Ball ball1;
Aim aim1;
bool onIsland = false;
int health, score, numMonsters = 10, nxtBoss = 2;
Island island1;
Chest chest1;
Boat boat1;
vector<Rock> rocks;
vector<Ball> enemyBalls;
vector<Barrel> barrels;
vector<Health> healths;
vector<Booster> boosters;
vector<Monster> monsters;
Sea sea1;
int maskArr[256];
glm::mat4 initVP;
vector<Display> displayList;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
bool lbutton_down = false;
bool rbutton_down = false;
float previous_x_position, previous_y_position;
int cameraView = 3;
int cnt, nxtShootcnt;
int boosterTimeLeft = -1;
// Camera View can take values:
// 0 = Boat View
// 1 = Top View
// 2 = Tower View
// 3 = Follow-cam View
// 4 = Helicopter-cam View
// 5 = Cinema View

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

    if(rbutton_down) {
        eye = boat1.position;
        eye.x -= 2.8*cos(PI * boat1.rotation / 180.0);
        eye.y -= 2.8*sin(PI * boat1.rotation / 180.0);
        eye.z += 3;
        target = eye;
        target.x -= 2*cos(PI * boat1.rotation / 180.0);
        target.y -= 2*sin(PI * boat1.rotation / 180.0);
        target.z += 2 * sin(PI * boat1.cannonRotation / 180.0);
    }
    else if(cameraView == 0) {
        eye = boat1.position;
        if(!onIsland) eye.x -= 6*cos(PI * boat1.rotation / 180.0);
        else eye.x -= 0.6*cos(PI * boat1.rotation / 180.0);
        if(!onIsland) eye.y -= 6*sin(PI * boat1.rotation / 180.0);
        else eye.y -= 0.6*sin(PI * boat1.rotation / 180.0);
        eye.z += 3;
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
        eye.z = 10;
        curEye = eye;
        curTarget = target;
    }
    else if(cameraView == 4) {
        eye = curEye;
        target = curTarget;
    }
    else if(cameraView == 5) {
        target = boat1.position;
        target.z = 2;
        if((curEye.x - target.x)*(curEye.x - target.x) + (curEye.y - target.y)*(curEye.y - target.y) > 100 * 100) {
            float rad = rand()%81, ang = (rand()%360) * PI / 180.0;
            curEye.x = target.x + rad * cos(ang);
            curEye.y = target.y + rad * sin(ang);
        }
        eye = curEye;
        eye.z = 60;
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
    for(auto&z: enemyBalls) {
        z.draw(VP);
    }
    if(onIsland) boat1.islandDraw(VP);
    else boat1.draw(VP);
    island1.draw(VP);
    chest1.draw(VP);
    for(auto&z: displayList) {
        z.draw(initVP);
    }
    if(rbutton_down) {
        aim1.draw(initVP);
    }

    for(auto&z: rocks) {
        z.draw(VP);
    }

    for(auto&z: barrels) {
        z.draw(VP);
    }

    for(auto&z: healths) {
        z.draw(VP);
    }

    for(auto&z: monsters) {
        z.draw(VP);
    }

    for(auto&z: boosters) {
        z.draw(VP);
    }

    glUseProgram (textureProgramID);
    sea1.draw(VP);
    if(!onIsland) boat1.texturedDraw(VP);
}

void startAudioPlayer(std::string fileName, bool isRepeating) {
    int forkPid = fork();
    if(forkPid == -1) {
        printf("Error occurred during forking.\n");
        exit(0);
    }
    if( forkPid == 0 ) {
        playAudio(fileName, isRepeating);
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    if(up) {
        boat1.velocity = 0.25;
        if(boosterTimeLeft>0) boat1.velocity = 0.4;
        boat1.handAngle += boat1.handAngularVelocity;
    }
    if(down) {
        boat1.velocity = -0.15;
        boat1.handAngle += -boat1.handAngularVelocity;
    }
    if(left) {
        boat1.rotation += 0.8;
    }
    if(right) {
        boat1.rotation -= 0.8;
    }
    if(rbutton_down) {
        double x;
        double y;
        glfwGetCursorPos(window, &x, &y);
        if(x > previous_x_position) {
            boat1.rotation -= 0.8;
        }
        else if(x < previous_x_position){
            boat1.rotation += 0.8;
        }
        if(y > previous_y_position) {
            boat1.cannonRotation -= 0.8;
            boat1.cannonRotation = max(boat1.cannonRotation, 0.0f);
        }
        else if(y < previous_y_position){
            boat1.cannonRotation += 0.8;
            boat1.cannonRotation = min(boat1.cannonRotation, 20.0f);
        }
        previous_x_position = x;
        previous_y_position = y;
    }
    if(rbutton_down or cameraView != 4) return;
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
    int dx = boat1.position.x - 100;
    int dy = boat1.position.y - 100;
    onIsland = (dx * dx + dy * dy) <= 31 * 31;
    ball1.tick();
    for(auto&z: enemyBalls) {
        z.tick();
    }
    if(!onIsland) boat1.tick();
    else boat1.islandTick(chest1.shape, chest1.broken);
    sea1.tick();
    for(auto&z: barrels) {
        z.tick();
    }
    for(auto&z: healths) {
        z.tick();
    }
    for(auto&z: boosters) {
        z.tick();
    }
    int idx = 0;
    for(auto&z: monsters) {
        glm::vec2 temp = (glm::vec2(boat1.position.x - z.position.x, boat1.position.y-z.position.y));
        temp = temp / length(temp);
        z.rotation = glm::orientedAngle(temp,glm::vec2(1, 0)) * -180 / PI;
        if(z.isBoss) {
            z.position.x += 0.12*temp.x;
            z.position.y += 0.12*temp.y;
            z.shape.position = z.position;
        }
        if((cnt & 255) == 0) {
            enemyBalls[idx].position = z.position;
            enemyBalls[idx].velocity.x = temp.x;
            enemyBalls[idx].velocity.y = temp.y;
            enemyBalls[idx].velocity.z = 0.1;
        }
        ++idx;
    }
    int oldRocksSz = rocks.size();
    rocks.erase(std::remove_if(rocks.begin(), rocks.end(), [](Rock &ro) {
        return detect_collision(ro.shape, boat1.shape);
    }), rocks.end());
    for(auto it = barrels.begin(); it != barrels.end();) {
        if(detect_collision(it->shape2, boat1.shape)) {
            score += 10;
            startAudioPlayer("pickup.mp3", false);
            it = barrels.erase(it);
        }
        else if(detect_collision(it->shape, boat1.shape)) {
            it = barrels.erase(it);
        }
        else {
            ++it;
        }
    }
    for(auto&z: enemyBalls) {
        if(detect_collision(z.shape, boat1.sphereShape)) {
            health -= 10;
            z.position.z -= 100;
        }
    }
    health -= (oldRocksSz - rocks.size())*5;
    for(auto it = healths.begin(); it != healths.end();) {
        if(detect_collision(it->shape, boat1.shape)) {
            startAudioPlayer("pickup.mp3", false);
            if(health < 100) health = 100;
            else health += 10;
            it = healths.erase(it);
        }
        else {
            ++it;
        }
    }
    for(auto it = monsters.begin(); it != monsters.end();) {
        if(detect_collision(it->shape, ball1.shape)) {
            if(it->isBoss > 1) {
                it->isBoss -= 1;
                ball1.position.z -= 10;
                ++it;
            }
            else if(it->isBoss == 1) {
                score += 200;
                boosters.push_back(Booster(it->position.x, it->position.y, color_t{255, 235, 59}));
                it = monsters.erase(it);
                ball1.position.z -= 10;
            }
            else {
                score += 50;
                healths.push_back(Health(it->position.x, it->position.y, color_t{236, 64, 122}));
                it = monsters.erase(it);
                ball1.position.z -= 10;
            }
        }
        else if(detect_collision(it->shape, boat1.shape)) {
            if(it->isBoss) health = 0;
            else health -= 40;
            it = monsters.erase(it);
        }
        else {
            ++it;
        }
    }
    if(detect_collision(chest1.shape, ball1.shape)) {
        chest1.broken = 1;
        ball1.position.z -= 10;
    }
    if(detect_collision(chest1.shape, boat1.humanShape) and chest1.broken == 1) {
        chest1.broken = 2;
        startAudioPlayer("pickup.mp3", false);
        score += 1000;
    }
    if(monsters.size() == numMonsters - nxtBoss){
        monsters.push_back(Monster(10, 10, color_t{236, 64, 122}, true));
        nxtBoss += 2;
    }
    for(auto it = boosters.begin(); it != boosters.end();) {
        if(detect_collision(it->shape, boat1.shape)) {
            boosterTimeLeft = 60 * 60;
            startAudioPlayer("pickup.mp3", false);
            it = boosters.erase(it);
        }
        else {
            ++it;
        }
    }
}

void initMasks() {
    maskArr[' '] = 0;
    maskArr['-'] = 0b10;
    maskArr['A'] = 0b1111011;
    maskArr['L'] = 0b101100;
    maskArr['V'] = 0b11010000;
    maskArr['H'] = 0b1111010;
    maskArr['E'] = 0b101111;
    maskArr['C'] = 0b101101;
    maskArr['T'] = 0b101001;
    maskArr['F'] = 0b101011;
    maskArr['N'] = 0b11111000;
    maskArr['m'] = 0b010101000;
    maskArr['M'] = 0b101010000;
    maskArr['R'] = 0b1111011;
    maskArr['X'] = 0b110000000;
    maskArr['0'] = maskArr['O'] = 0b1111101;
    maskArr['I'] = maskArr['1'] = 0b1010000;
    maskArr['2'] = 0b0110111;
    maskArr['3'] = 0b1010111;
    maskArr['4'] = 0b1011010;
    maskArr['S'] = maskArr['5'] = 0b1001111;
    maskArr['6'] = 0b1101111;
    maskArr['7'] = 0b1010001;
    maskArr['B'] = maskArr['8'] = 0b1111111;
    maskArr['9'] = 0b1011111;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(0, 0, color_t{239, 108, 0});
    boat1 = Boat(-15, 0, color_t{62, 39, 35}, COLOR_RED, color_t{255, 87, 34});
    sea1 = Sea(0, 2, COLOR_BLUE);
    island1 = Island(100, 100, color_t{255, 255, 141});
    chest1 = Chest(100, 100, color_t{109, 32, 8});
    aim1 = Aim(0, 0, COLOR_BLACK);
    // healths.push_back(Health(0, 0, color_t{236, 64, 122}));
    // boosters.push_back(Booster(3, 3, color_t{255, 235, 59}));
    for(int i=0; i<numMonsters; ++i) {
        monsters.emplace_back(Monster((rand() % 501) - 250, (rand() % 501) - 250, color_t{236, 64, 122}, false));
        enemyBalls.emplace_back(Ball(0, 0, color_t{239, 108, 0}, 0.005));
    }
    monsters.erase(std::remove_if(monsters.begin(), monsters.end(), [](Monster &mo) {
        int dx = mo.position.x - 100;
        int dy = mo.position.y - 100;
        return (dx * dx + dy * dy) <= 30 * 30;
    }), monsters.end());
    for(int i=0; i<70; ++i) {
        rocks.emplace_back(Rock((rand() % 2001) - 1000, (rand() % 2001) - 1000, COLOR_BLACK));
    }
    rocks.erase(std::remove_if(rocks.begin(), rocks.end(), [](Rock &ro) {
        int dx = ro.position.x - 100;
        int dy = ro.position.y - 100;
        return (dx * dx + dy * dy) <= 30 * 30;
    }), rocks.end());

    for(int i=0; i<70; ++i) {
        barrels.emplace_back(Barrel((rand() % 2001) - 1000, (rand() % 2001) - 1000, color_t{150, 111, 51}, color_t{129, 212, 250}));
    }

    barrels.erase(std::remove_if(barrels.begin(), barrels.end(), [](Barrel &ba) {
        int dx = ba.position.x - 100;
        int dy = ba.position.y - 100;
        return (dx * dx + dy * dy) <= 30 * 30;
    }), barrels.end());

    initVP = glm::ortho(-4*16.0f/9, 4*16.0f/9, -4.0f, 4.0f, 0.1f, 500.0f) * glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    textureProgramID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );

    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    // Get a handle for our "MVP" uniform
    textureMatrixID = glGetUniformLocation(textureProgramID, "MVP");
    TextureID  = glGetUniformLocation(textureProgramID, "myTextureSampler");

    for(int i=0; i<70; ++i) {
        displayList.push_back(Display((-4 * 16.0/9) + 0.1 + i*0.2, 3.8, COLOR_BLACK, maskArr[' ']));
    }
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

void cannonShoot() {
    startAudioPlayer("cannon.mp3", false);
    nxtShootcnt = cnt + 180;
    ball1.position = boat1.position - glm::vec3(2.8*cos(PI * boat1.rotation / 180.0), 2.8*sin(PI * boat1.rotation / 180.0), -1.7);
    ball1.velocity.x = -cos(PI * boat1.rotation / 180.0);
    ball1.velocity.y = -sin(PI * boat1.rotation / 180.0);
    ball1.velocity.z = 2*sin(PI * boat1.cannonRotation / 180.0);
}

void inputHandler(int key, int action) {
    if(key == GLFW_KEY_V) {
        if(action == GLFW_PRESS) {
            cameraView = (cameraView + 1) % 6;
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
    if(rbutton_down and key == GLFW_KEY_F) {
        if(action == GLFW_PRESS and nxtShootcnt < cnt) {
            cannonShoot();
        }
    }
}

void scrollHandler(double offset) {
    if(cameraView != 4) return;
    glm::vec3 dir;
    if(offset > 0) dir = curTarget - curEye;
    else if(offset < 0) dir = curEye - curTarget;
    else return;
    dir = dir/(10*glm::length(dir));
    curEye = dir + curEye;
    curTarget = dir + curTarget;
    if(curEye.z < 1.0f) {
        curTarget.z += 1.0f - curEye.z;
        curEye.z = 1.0f;
    }

}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1600;
    int height = 900;
    score = 0;
    health = 100;
    cnt = 0, nxtShootcnt = -1;

    startAudioPlayer("song.mp3", true);

    window = initGLFW(width, height);

    initMasks();
    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if(t60.processTick()) {
            // 60 fps
            ++cnt;
            // OpenGL Draw commands
            draw();
            --boosterTimeLeft;
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);

            if(boosterTimeLeft > 0) {
                sprintf(windowTitle, "SCORE-%d  HEALTH-%d BOOST LEFT - %d", score, health, (boosterTimeLeft+59)/60);
            }
            else {
                sprintf(windowTitle, "SCORE-%d  HEALTH-%d", score, health);
            }

            if(health <= 0) {
                printf("Your score was %d.\n", score);
                exit(0);
            }

            for(int i=0; i<displayList.size(); ++i) {
                displayList[i].mask = maskArr[' '];
            }

            for(int i=0; windowTitle[i]!='\0'; ++i) {
                displayList[i].mask = maskArr[windowTitle[i]];
            }

            if((cnt & 511) == 0) {
                boat1.oldWindAngle = boat1.windAngle;
                boat1.windRatio = 0;
                boat1.windAngle = rand()%360;
            }
            if(cos((boat1.windAngle - boat1.rotation)*PI/180.0) > 0.3) {
                if(boat1.mastScale != 1) {
                    boat1.mastRatio = 0;
                    boat1.oldMastScale = boat1.mastScale;
                    boat1.mastScale = 1;
                }
            }
            else {
                if(boat1.mastScale != 0) {
                    boat1.mastRatio = 0;
                    boat1.oldMastScale = boat1.mastScale;
                    boat1.mastScale = 0;
                }
            }
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
    exit(0);
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
