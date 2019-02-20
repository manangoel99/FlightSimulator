#include "main.h"
#include "timer.h"
#include "ball.h"
#include "plane.h"
#include "sea.h"
#include "enemy.h"
#include "dashboard.h"
#include "weaponry.h"
#include "powerups.h"
#include "scoreboard.h"
#include "checkpoints.h"

#define ll long long

using namespace std;

GLMatrices Matrices;
GLMatrices Matrices1;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Plane plane;
Sea sea;

Segments one;
Segments ten;
Segments hundred;

vector <SmokeRing> rings;
vector <Volcano> vols;
vector <Canon> canons;
vector <CanonBall> balls;
vector <Bomb> bombs;
vector <Missile> missiles;
vector <Parachute> parachutes;
vector <Bullet> bullets;
vector <LifePowerUp> lifepowerups;
vector <FuelPowerUp> fuelpowerups;
vector <CheckPoint> checkpoints;

vector <pair <bool, CheckPoint> > Memo;
int score = 0;

ll num_ticks = 0;
LifeBar lifebar;
HeightBar heightbar;
Compass compass;
FuelGauge fuelgauge;
Arrow arrow;

bool MousePress = false;
int camera_view = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float heli_rad = 5.0f;

Timer t60(1.0 / 60);
Timer t1(1.0 / 1);

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
    glm::vec3 up1(0, 1, 0);
    glm::vec3 eye1(0, 0, 5);
    glm::vec3 target1(0, 0, 0);
    //Matrices1.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    Matrices1.view = glm::lookAt(eye1, target1, up1);
    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP1 = Matrices.projection * Matrices1.view;

    one.draw(VP1);
    ten.draw(VP1);
    hundred.draw(VP1);
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    // Scene render
    //ball1.draw(VP);
    sea.draw(VP);
    compass.draw(VP1);
    //c.draw(VP, plane.position);
    fuelgauge.draw(VP1);

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

    for (vector <Bomb>::iterator i = bombs.begin(); i != bombs.end(); i++) {
        i->draw(VP);
    }

    for (vector <Missile>::iterator i = missiles.begin(); i != missiles.end(); i++) {
        i->draw_left(VP);
        i->draw_right(VP);
    }

    for (vector <Parachute>::iterator i = parachutes.begin(); i != parachutes.end(); i++) {
        i->draw(VP);
    }

    for (vector <Bullet>::iterator i = bullets.begin(); i != bullets.end(); i++) {
        i->draw(VP);
    }

    for (vector <LifePowerUp>::iterator i = lifepowerups.begin(); i != lifepowerups.end(); i++) {
        i->draw(VP);
    }

    for (vector <FuelPowerUp>::iterator i = fuelpowerups.begin(); i != fuelpowerups.end(); i++) {
        i->draw(VP);
    }

    for (vector <CheckPoint>::iterator i = checkpoints.begin(); i != checkpoints.end(); i++) {
        i->draw(VP);
    }

    vector <CheckPoint>::iterator i = checkpoints.begin();

    arrow.draw(VP, plane, *i);

    lifebar.draw(VP1);
    heightbar.draw(VP1);
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
        eye = glm::vec3(100, 100, 100);    //Tower
        target = plane.position;
    }
    else if (camera_view == 3) {
        eye = glm::vec3(plane.position.x + 2.5 * cos(plane.pitch * M_PI / 180), plane.position.y + 1, plane.position.z - 2.5 * sin(plane.pitch * M_PI / 180));
        target = glm::vec3(plane.position.x + 4 * cos(plane.pitch * M_PI / 180), plane.position.y , plane.position.z - 4 * sin(plane.pitch * M_PI / 180));
    }
    else if (camera_view == 4) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        double phi = 0.01 * (540 - xpos);
        double theta = 0.01 * (540 - ypos);

        eye = glm::vec3(plane.position.x + heli_rad * cos(theta) * sin(phi), plane.position.y + heli_rad * sin(theta), plane.position.z + heli_rad * cos(theta) * cos(phi));

        //cout << xpos << '\t' << ypos << endl;
        target = glm::vec3(plane.position.x, plane.position.y, plane.position.z);
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
    int left_click = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int right_click = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

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
            camera_view = 3;
        }
        else if (camera_view == 3) {
            eye = glm::vec3(plane.position.x + 2 * cos(plane.pitch * M_PI / 180), plane.position.y, plane.position.z + 2 * sin(plane.pitch * M_PI / 180));
            target = glm::vec3(plane.position.x + 4 * cos(plane.pitch * M_PI / 180), plane.position.y, plane.position.z + 4 * sin(plane.pitch * M_PI / 180));
            camera_view = 4;
        }
        else if (camera_view == 4) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            double phi = 0.01 * (400 - xpos);
            double theta = 0.01 * (400 - ypos);

            eye = glm::vec3(plane.position.x + heli_rad * cos(theta) * sin(phi), heli_rad * sin(theta), heli_rad * cos(theta) * cos(phi));

            //cout << xpos << '\t' << ypos << endl;
            target = glm::vec3(plane.position.x, plane.position.y, plane.position.z);
            camera_view = 0;
        }
        CAMERA_CHANGE_VAR = 1;
    }
    else if (c == GLFW_RELEASE) {
        CAMERA_CHANGE_VAR = 0;
    }

    if (left_click == GLFW_PRESS && MousePress == false) {
        Bomb b = Bomb(plane.position.x, plane.position.y, plane.position.z, plane);
        bombs.push_back(b);
        MousePress = true;
    }

    if (right_click == GLFW_PRESS && MousePress == false) {
        Missile m = Missile(plane);
        missiles.push_back(m);
        MousePress = true;
    }

    if (right_click == GLFW_RELEASE && left_click == GLFW_RELEASE) {
        MousePress = false;
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
        plane.roll -= 1;
    }

    if (e) {
        plane.roll += 1;
    }



    if (!up && !down) {
        if (plane.yaw > 0) {
            plane.yaw -= 0.25;
        }
        if (plane.yaw < 0) {
            plane.yaw += 0.25;
        }
    }

    if (!left and !right and !q and !e) {
        if (plane.roll > 0 && (int)(plane.roll) % 360 != 0) {
            plane.roll--;
        }
        else if (plane.roll < 0 && (int)(plane.roll) % 360 != 0) {
            plane.roll++;
        }
    }
}

void tick_elements() {
    ball1.tick();
    plane.tick();
    updatecam();

    num_ticks++;

    compass.set_rotation(plane);

    fuelgauge.set_fuel(plane);

    if (plane.life <= 0 || plane.fuel <= 0 || plane.position.y <= -4) {
        quit(window);
    }

    int ones = score % 10;

    int tens = score / 10;
    tens = tens % 10;

    int hundereds = score / 100;

    one.set_number(ones);
    hundred.set_number(hundereds);
    ten.set_number(tens);

    if (num_ticks % 653 == 0) {
        LifePowerUp l = LifePowerUp(rand() % 300, rand() % 30, rand() % 300);
        lifepowerups.push_back(l);
    }

    if (num_ticks % 727 == 0) {
        FuelPowerUp f = FuelPowerUp(rand() % 300, rand() % 30, rand() % 300);
        fuelpowerups.push_back(f);
    }

    for (vector <SmokeRing>::iterator it = rings.begin(); it != rings.end(); it++) {
        if(it->DetectPassing(plane) == true) {
            rings.erase(it);
            score += 10;
            it--;
            break;
        }
    }

    for (vector <LifePowerUp>::iterator it = lifepowerups.begin(); it != lifepowerups.end(); it++) {
        if (it->CheckCollision(plane)) {
            if (plane.life <= 35) {
                plane.life += 5;
            }
            else {
                plane.life = 40;
            }

            lifepowerups.erase(it);
            it--;
            break;
        }
    }

    for (vector <FuelPowerUp>::iterator it = fuelpowerups.begin(); it != fuelpowerups.end(); it++) {
        if (it->CheckCollision(plane)) {
            if (plane.life <= 95) {
                plane.fuel += 5;
            }
            else {
                plane.life = 100;
            }

            fuelpowerups.erase(it);
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
        if (i->detect_collision(plane)) {
            //cout << "TERI MAA CHUD GYI" << endl;
            plane.life -= 5;
            //cout << plane.life << endl;
            balls.erase(i);
            i--;
            break;
        }
    }
    for (vector <Bomb>::iterator i = bombs.begin(); i != bombs.end(); i++) {
        i->tick();
        if (i->position.y <= -4) {
            bombs.erase(i);
            i--;
            break;
        }
        for (vector <Canon>::iterator it = canons.begin(); it != canons.end(); it++) {
            if(i->detect_collision(*it)) {

                for (vector <pair <bool, CheckPoint> >::iterator ite = Memo.begin(); ite != Memo.end(); ite++) {
                    if (ite->second.position.x >= it->position.x && ite->second.position.x <= it->position.x + 4) {
                        if (ite->second.position.z >= it->position.z && ite->second.position.z <= it->position.z + 4) {
                            ite->first = true;
                            //cout << "HUHUAHUA" << endl;
                        }
                        
                    }
                }

                canons.erase(it);
                it--;
                score += 10;
                break;
            }
        }
    }

    if (num_ticks % 120 == 0) {
        ll n = rand() % 10;

        int x = rand() % 3;

        glm::vec3 planevec;

        if (x == 0) {
            planevec = plane.position - canons[n].position + glm::vec3(0, 0.2, 0);
        }
        else if (x == 1) {
            planevec = plane.position - canons[n].position;
        } else if (x == 2) {
            planevec = plane.position - canons[n].position - glm::vec3(0, 0.2, 0);
        }
        CanonBall c1 = CanonBall(canons[n].position.x, canons[n].position.y, canons[n].position.z, planevec);
        balls.push_back(c1);
    }

    if (num_ticks % 247 == 0) {
        Parachute p = Parachute(rand() % 300, 40, rand() % 300);
        parachutes.push_back(p);
    }

    if (num_ticks % 127 == 0) {

        ll z = parachutes.size();
        ll n;
        if (z != 0) {
            n = rand() % z;

            int x = rand() % 3;
    
            glm::vec3 planevec;

            if (x == 0) {
                planevec = plane.position - parachutes[n].position + glm::vec3(0, 0.2, 0);
            }
            else if (x == 1) {
                planevec = plane.position - parachutes[n].position;
            } else if (x == 2) {
                planevec = plane.position - parachutes[n].position - glm::vec3(0, 0.2, 0);
            }

            Bullet b = Bullet(parachutes[n].position.x, parachutes[n].position.y, parachutes[n].position.y, planevec);
            bullets.push_back(b);
        }
    }

    for (vector <Missile>::iterator i = missiles.begin(); i != missiles.end(); i++) {
        i->tick();
        if (i->left_position.y <= -4) {
            missiles.erase(i);
            i--;
            break;
        }

        for (vector <Canon>::iterator it = canons.begin(); it != canons.end(); it++) {
            if (i->CanonCollision(*it)) {

                for (vector <pair <bool, CheckPoint> >::iterator ite = Memo.begin(); ite != Memo.end(); ite++) {
                    if (ite->second.position.x >= it->position.x && ite->second.position.x <= it->position.x + 4) {
                        if (ite->second.position.z >= it->position.z && ite->second.position.z <= it->position.z + 4) {
                            ite->first = true;
                            //cout << "HUHUAHUA" << endl;
                        }
                        
                    }
                }

                canons.erase(it);
                missiles.erase(i);
                it--;
                i--;
                score += 10;
                break;
            }
        }

        for (vector <Parachute>::iterator it = parachutes.begin(); it != parachutes.end(); it++) {
            if (i->ParachuteCollision(*it)) {
                cout << "Phod Diya" << endl;
                parachutes.erase(it);
                missiles.erase(i);
                it--;
                i--;
                score += 5;
                break;
            }
        }

    }

    for (vector <Parachute>::iterator it = parachutes.begin(); it != parachutes.end(); it++) {

        it->tick();
        if (it->position.y <= -7) {
            parachutes.erase(it);
            it--;
            break;
        }
    }

    for (vector <Bullet>::iterator i = bullets.begin(); i != bullets.end(); i++) {
        i->tick();
        if (i->detect_collision(plane)) {
            plane.life--;
            bullets.erase(i);
            i--;
            break;
        }
    }

    for (vector <CheckPoint>::iterator it = checkpoints.begin(); it != checkpoints.end(); it++) {
        if (it->DetectPassing(plane)) {
            bool flag = false;
            for (vector <pair <bool, CheckPoint> >::iterator ite = Memo.begin(); ite != Memo.end(); ite++) {
                if (ite->second.position == it->position && ite->first == true) {
                    checkpoints.erase(it);
                    it--;
                    flag = true;
                    break;
                }
            }
            if (flag == true) {
                break;
            }
        }
    }

    arrow.position.x = plane.position.x + 2 * cos(plane.pitch * M_PI / 180);
    arrow.position.z = plane.position.z - 2 * sin(plane.pitch * M_PI / 180);
    arrow.position.y = plane.position.y + 2;

    lifebar.CreateLifeObject(plane);
    heightbar.UpdateBar(plane);
    //camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0, 2, COLOR_RED);
    plane       = Plane(0, 20, 0, COLOR_BLACK);
    sea         = Sea(0, 0, 0, COLOR_BLUE);
    //c           = Canon(0 , 0, 0);
    lifebar     = LifeBar(-12, 11, 0);
    heightbar   = HeightBar(-12, 10, 0);
    lifebar.CreateLifeObject(plane);
    compass     = Compass(10, 10, 0);
    fuelgauge   = FuelGauge(-12, 9, 0, plane);
    arrow       = Arrow(0.0, 7, 0);

    one         = Segments(0.6, 10.5, 0);
    ten         = Segments(-0.3, 10.5, 0);
    hundred     = Segments(-1.0, 10.5, 0);

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
        canons.push_back(c);

        CheckPoint c1 = CheckPoint(c.position.x + (rand() % 5), rand() % 30, c.position.z + (rand() % 5));
        checkpoints.push_back(c1);

        Memo.push_back(make_pair(false, c1));
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

        if (t1.processTick()) {
            plane.fuel -= 1;
            score += 1;
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
    Matrices1.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(135 * M_PI / 180, 1.0, 0.1, 100.0);
}
