#include "main.h"
#include "timer.h"
#include "ball.h"
#include "plane.h"
#include "sea.h"
#include "enemy.h"

#define ll long long

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Plane plane;
Sea sea;
vector <SmokeRing> rings;
vector <Volcano> vols;
vector <Canon> canons;
vector <CanonBall> balls;
ll num_ticks = 0;

int camera_view = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

int CAMERA_CHANGE_VAR = 0;

glm::vec3 eye(-1.5, 3, 0);
// Target - Where is the camera looking at.  Don't change unless you are sure!!
glm::vec3 target(0, 0, 0);
// Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
glm::vec3 up(0, 1, 0);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    //glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );

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
    //ball1.draw(VP);
    sea.draw(VP);
    //c.draw(VP, plane.position);

    for (vector <SmokeRing>::iterator it = rings.begin(); it != rings.end(); it++) {
        it->draw(VP);
    }

    for(vector <Volcano>::iterator i = vols.begin(); i != vols.end(); i++) {
        i->draw(VP);
    }

    for (vector <Canon>::iterator i = canons.begin(); i != canons.end(); i++) {
        glm::vec3 planevec = plane.position - i->position;
        i->draw(VP, planevec);
        i->drawdisc(VP);
    }

    for (vector <CanonBall>::iterator i = balls.begin(); i != balls.end(); i++) {
        i->draw(VP);
    }

    plane.draw(VP);
}

void updatecam() {
    if (camera_view == 0) {
        eye = glm::vec3(plane.position.x - 1.5 * cos(plane.pitch * M_PI / 180), plane.position.y + 3, plane.position.z + 1.5 * sin(plane.pitch * M_PI / 180)); //Follow-Cam
        target = plane.position;
    }
    else if (camera_view == 1) {
        eye = glm::vec3(plane.position.x + 0.1, plane.position.y + 5, plane.position.z);    //Top
        target = plane.position;
    }
    else if (camera_view == 2) {
        eye = glm::vec3(10, 10, 10);    //Tower
        target = plane.position;
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int c = glfwGetKey(window, GLFW_KEY_C);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int forward = glfwGetKey(window, GLFW_KEY_W);
    int q = glfwGetKey(window, GLFW_KEY_Q);
    int e = glfwGetKey(window, GLFW_KEY_E);

    if (c == GLFW_PRESS && CAMERA_CHANGE_VAR == 0) {
        if (camera_view == 0) {         //Follow-Cam
            eye = glm::vec3(plane.position.x - 1.5 * cos(plane.pitch * M_PI / 180), plane.position.y + 3, plane.position.z * sin(plane.pitch * M_PI / 180)); //Follow-Cam
            target = plane.position;            //Follow-Cam
            camera_view++;          //Follow-Cam
        }
        else if (camera_view == 1) {     //Top View
            eye = glm::vec3(plane.position.x + 0.1, plane.position.y + 5, plane.position.z);     //Top View
            target = plane.position;     //Top View
            camera_view++;
        }
        else if (camera_view == 2) {
            eye = glm::vec3(5, 5, 5); //Tower
            target = plane.position;
            camera_view = 0;
        }
        CAMERA_CHANGE_VAR = 1;
    }
    else if (c == GLFW_RELEASE) {
        CAMERA_CHANGE_VAR = 0;
    }

    if (up) {
        plane.position.y += 0.05;
        if (plane.yaw <= 30)
            plane.yaw += 0.1;
    }

    if (down) {
        plane.position.y -= 0.05;
        if (plane.yaw >= -30)
            plane.yaw -= 0.1;
    }

    if (forward) {
        plane.position.x += 0.1 * cos(plane.pitch * M_PI / 180);
        plane.position.z -= 0.1 * sin(plane.pitch * M_PI / 180);
    }

    if (left) {
        plane.pitch += 1;
        if (plane.roll > -5) {
            plane.roll -= 1;
        }
    }

    if (right) {
        plane.pitch -= 1;
        if (plane.roll < 5) {
            plane.roll += 1;
        }
    }

    if (q) {
        plane.roll += 1;
    }

    if (e) {
        plane.roll -= 1;
    }



    if (!up && !down) {
        if (plane.yaw > 0) {
            plane.yaw -= 0.25;
        }
        if (plane.yaw < 0) {
            plane.yaw += 0.25;
        }
    }

    if (!left and !right) {
        if (plane.roll > 0) {
            plane.roll--;
        }
        else if (plane.roll < 0) {
            plane.roll++;
        }
    }
}

void tick_elements() {
    ball1.tick();
    plane.tick();
    updatecam();

    num_ticks++;

    for (vector <SmokeRing>::iterator it = rings.begin(); it != rings.end(); it++) {
        if(it->DetectPassing(plane) == true) {
            rings.erase(it);
            it--;
            break;
        }
    }

    for (vector <Volcano>::iterator it = vols.begin(); it != vols.end(); it++) {
        if(it->DetectPassing(plane) == true) {
            //cout << it->position.x << '\t' << it->position.z << endl;
            quit(window);
        }
    }
    for (vector <CanonBall>::iterator i = balls.begin(); i != balls.end(); i++) {
        i->tick();
    }

    if (num_ticks % 120 == 0) {
        ll n = rand() % 10;
        glm::vec3 planevec = plane.position - canons[n].position;
        CanonBall c1 = CanonBall(canons[n].position.x, canons[n].position.y, canons[n].position.z, planevec);
        cout << c1.position.x << '\t' << c1.position.y << '\t' << c1.position.z << endl;
        balls.push_back(c1);
    }
    //camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0, 2, COLOR_RED);
    plane       = Plane(0, 1, 0, COLOR_BLACK);
    sea         = Sea(0, 0, 0, COLOR_BLUE);
    //c           = Canon(0 , 0, 0);

    for (ll i = 0; i < 50; i++) {
        SmokeRing r = SmokeRing(rand() % 300, rand() % 30, rand() % 300);
        rings.push_back(r);
    }

    for (ll i = 0; i < 15; i++) {
        Volcano v = Volcano(rand() % 300, -4, rand() % 300);
        vols.push_back(v);
    }

    for (ll i = 0; i < 10; i++) {
        Canon c = Canon(rand() % 300, -4, rand() % 300);
        cout << c.position.x << '\t' << c.position.y << '\t' << c.position.z << endl;
        canons.push_back(c);
    }

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


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1080;
    int height = 1080;

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
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(135 * M_PI / 180, 1.0, 0.1, 100.0);
}
