#include "main.h"
#include "weaponry.h"
#define ll long long

Bomb::Bomb(float x, float y, float z, Plane plane) {
    this->position = glm::vec3(x, y, z);
    GLfloat vertex_buffer_data[20000];

    float radius = 1;
    ll n = 1000;

    double theta = 0;

    this->velocity = glm::vec3(0.0, 0, 0);
    this->acc = glm::vec3(0.0, -0.025, 0.0);

    for (ll i = 0; i < 9 * n; i += 9) {
        vertex_buffer_data[i] = radius * cos(theta);
        vertex_buffer_data[i + 1] = 0;
        vertex_buffer_data[i + 2] = radius * sin(theta);

        vertex_buffer_data[i + 3] = 0;
        vertex_buffer_data[i + 4] = -2;
        vertex_buffer_data[i + 5] = 0;

        vertex_buffer_data[i + 6] = radius * cos(theta + (2 * M_PI / n));
        vertex_buffer_data[i + 7] = 0;
        vertex_buffer_data[i + 8] = radius * sin(theta + (2 * M_PI / n));

        theta += (2 * M_PI) / n;
    }

    this->object = create3DObject(GL_TRIANGLES, 3 * n, vertex_buffer_data, COLOR_BROWN, GL_FILL);

}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bomb::tick() {
    this->position += this->velocity;
    this->velocity += this->acc;
}

bool Bomb::detect_collision(Canon canon) {
    float z = (this->position.x - canon.position.x) * (this->position.x - canon.position.x);
    z += (this->position.z - canon.position.z) * (this->position.z - canon.position.z);

    z = z - 9;

    if (z <= 0 and this->position.y - 2 <= -3.9) {
        return true;
    }
    else {
        return false;
    }
}

Missile::Missile(Plane plane) {
    this->left_position = glm::vec3(plane.position.x, plane.position.y, plane.position.z);
    this->right_position = glm::vec3(plane.position.x, plane.position.y, plane.position.z);
    this->pitch = plane.pitch;
    this->yaw = plane.yaw;
    this->roll = plane.roll;
    this->acc = glm::vec3(0, -0.05, 0);

    this->velocity = glm::vec3(5 * (cos(plane.pitch * (M_PI / 180)) * cos(plane.yaw * (M_PI / 180))), 5 * sin(plane.yaw * (M_PI / 180)), -5 * sin(plane.pitch * M_PI / 180));

    GLfloat left_coord_missile[50000];
    GLfloat right_coord_missile[50000];

    float theta = 0;

    float r = 0.25f;

    ll n = 1000;

    for (ll i = 0; i < 9 * n; i += 9)
    {
        left_coord_missile[i] = 1;
        left_coord_missile[i + 1] = r * sin(theta);
        left_coord_missile[i + 2] = r * cos(theta);
        left_coord_missile[i + 3] = 1.5;
        left_coord_missile[i + 4] = 0;
        left_coord_missile[i + 5] = 0;
        left_coord_missile[i + 6] = 1;
        left_coord_missile[i + 7] = r * sin(theta + (2 * M_PI) / n);
        left_coord_missile[i + 8] = r * cos(theta + (2 * M_PI) / n);

        right_coord_missile[i] = 1;
        right_coord_missile[i + 1] = r * sin(theta);
        right_coord_missile[i + 2] = r * cos(theta);
        right_coord_missile[i + 3] = 1.5;
        right_coord_missile[i + 4] = 0;
        right_coord_missile[i + 5] = 0;
        right_coord_missile[i + 6] = 1;
        right_coord_missile[i + 7] = r * sin(theta + (2 * M_PI) / n);
        right_coord_missile[i + 8] = r * cos(theta + (2 * M_PI) / n);

        theta += ((2 * M_PI) / n);
    }

    theta = 0;

    for (ll i = 9 * n; i < 27 * n; i += 18)
    {
        left_coord_missile[i] = 0;
        left_coord_missile[i + 1] = r * sin(theta);
        left_coord_missile[i + 2] = r * cos(theta);

        left_coord_missile[i + 3] = 1;
        left_coord_missile[i + 4] = r * sin(theta);
        left_coord_missile[i + 5] = r * cos(theta);

        left_coord_missile[i + 6] = 0;
        left_coord_missile[i + 7] = r * sin(theta + (2 * M_PI) / n);
        left_coord_missile[i + 8] = r * cos(theta + (2 * M_PI) / n);

        left_coord_missile[i + 9] = 0;
        left_coord_missile[i + 10] = r * sin(theta + (2 * M_PI) / n);
        left_coord_missile[i + 11] = r * cos(theta + (2 * M_PI) / n);

        left_coord_missile[i + 12] = 1;
        left_coord_missile[i + 13] = r * sin(theta);
        left_coord_missile[i + 14] = r * cos(theta);

        left_coord_missile[i + 15] = 1;
        left_coord_missile[i + 16] = r * sin(theta + (2 * M_PI) / n);
        left_coord_missile[i + 17] = r * cos(theta + (2 * M_PI) / n);

        right_coord_missile[i] = 0;
        right_coord_missile[i + 1] = r * sin(theta);
        right_coord_missile[i + 2] = r * cos(theta);

        right_coord_missile[i + 3] = 1;
        right_coord_missile[i + 4] = r * sin(theta);
        right_coord_missile[i + 5] = r * cos(theta);

        right_coord_missile[i + 6] = 0;
        right_coord_missile[i + 7] = r * sin(theta + (2 * M_PI) / n);
        right_coord_missile[i + 8] = r * cos(theta + (2 * M_PI) / n);

        right_coord_missile[i + 9] = 0;
        right_coord_missile[i + 10] = r * sin(theta + (2 * M_PI) / n);
        right_coord_missile[i + 11] = r * cos(theta + (2 * M_PI) / n);

        right_coord_missile[i + 12] = 1;
        right_coord_missile[i + 13] = r * sin(theta);
        right_coord_missile[i + 14] = r * cos(theta);

        right_coord_missile[i + 15] = 1;
        right_coord_missile[i + 16] = r * sin(theta + (2 * M_PI) / n);
        right_coord_missile[i + 17] = r * cos(theta + (2 * M_PI) / n);

        theta += ((2 * M_PI) / n);
    }

    theta = 0;

    for (ll i = 27 * n; i < 45 * n; i += 18)
    {
        left_coord_missile[i] = 0;
        left_coord_missile[i + 1] = r * sin(theta);
        left_coord_missile[i + 2] = r * cos(theta);

        left_coord_missile[i + 3] = -1;
        left_coord_missile[i + 4] = r * sin(theta);
        left_coord_missile[i + 5] = r * cos(theta);

        left_coord_missile[i + 6] = 0;
        left_coord_missile[i + 7] = r * sin(theta + (2 * M_PI) / n);
        left_coord_missile[i + 8] = r * cos(theta + (2 * M_PI) / n);

        left_coord_missile[i + 9] = 0;
        left_coord_missile[i + 10] = r * sin(theta + (2 * M_PI) / n);
        left_coord_missile[i + 11] = r * cos(theta + (2 * M_PI) / n);

        left_coord_missile[i + 12] = -1;
        left_coord_missile[i + 13] = r * sin(theta);
        left_coord_missile[i + 14] = r * cos(theta);

        left_coord_missile[i + 15] = -1;
        left_coord_missile[i + 16] = r * sin(theta + (2 * M_PI) / n);
        left_coord_missile[i + 17] = r * cos(theta + (2 * M_PI) / n);

        right_coord_missile[i] = 0;
        right_coord_missile[i + 1] = r * sin(theta);
        right_coord_missile[i + 2] = r * cos(theta);

        right_coord_missile[i + 3] = -1;
        right_coord_missile[i + 4] = r * sin(theta);
        right_coord_missile[i + 5] = r * cos(theta);

        right_coord_missile[i + 6] = 0;
        right_coord_missile[i + 7] = r * sin(theta + (2 * M_PI) / n);
        right_coord_missile[i + 8] = r * cos(theta + (2 * M_PI) / n);

        right_coord_missile[i + 9] = 0;
        right_coord_missile[i + 10] = r * sin(theta + (2 * M_PI) / n);
        right_coord_missile[i + 11] = r * cos(theta + (2 * M_PI) / n);

        right_coord_missile[i + 12] = -1;
        right_coord_missile[i + 13] = r * sin(theta);
        right_coord_missile[i + 14] = r * cos(theta);

        right_coord_missile[i + 15] = -1;
        right_coord_missile[i + 16] = r * sin(theta + (2 * M_PI) / n);
        right_coord_missile[i + 17] = r * cos(theta + (2 * M_PI) / n);

        theta += ((2 * M_PI) / n);
    }

    for (ll i = 0; i < 45 * n; i++) {
        if (i % 3 == 2) {
            left_coord_missile[i] += 2.0f;
            right_coord_missile[i] -= 2.0f;
        }
        if (i % 3 == 1) {
            left_coord_missile[i] -= 0.25f;
            right_coord_missile[i] -= 0.25f;
        }
    }

    this->left_object = create3DObject(GL_TRIANGLES, 15 * n + 3, left_coord_missile, COLOR_RED, GL_FILL);
    this->right_object = create3DObject(GL_TRIANGLES, 15 * n + 3, right_coord_missile, COLOR_RED, GL_FILL);
}

void Missile::draw_left(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->left_position); // glTranslatef
    //glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 1));
    glm::mat4 mat_pitch = glm::rotate((float)(this->pitch * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 mat_roll = glm::rotate((float)(this->roll * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 mat_yaw = glm::rotate((float)(this->yaw * M_PI / 180.0f), glm::vec3(sin(M_PI * this->pitch / 180), 0, cos(M_PI * this->pitch / 180)));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * mat_yaw * mat_pitch * mat_roll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->left_object);
}

void Missile::draw_right(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->right_position); // glTranslatef
    //glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 1));
    glm::mat4 mat_pitch = glm::rotate((float)(this->pitch * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 mat_roll = glm::rotate((float)(this->roll * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 mat_yaw = glm::rotate((float)(this->yaw * M_PI / 180.0f), glm::vec3(sin(M_PI * this->pitch / 180), 0, cos(M_PI * this->pitch / 180)));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * mat_yaw * mat_pitch * mat_roll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->right_object);

}

void Missile::tick() {
    this->left_position += this->velocity;
    this->right_position += this->velocity;
    this->velocity += this->acc;
}

bool Missile::CanonCollision(Canon canon) {
    float left_x = this->left_position.x + 1.5 * cos(this->pitch * M_PI / 180) * cos(this->yaw * M_PI / 180);
    float left_y = this->left_position.y - 0.25f * sin(this->yaw * M_PI / 180);
    float left_z = this->left_position.z + 2.0f;

    float right_x = this->right_position.x + 1.5 * cos(this->pitch * M_PI / 180) * cos(this->yaw * M_PI / 180);
    float right_y = this->right_position.y - 0.25f * sin(this->yaw * M_PI / 180);
    float right_z = this->right_position.z - 2.0f;

    bool left_in;
    bool right_in;

    float Left = (left_x - canon.position.x) * (left_x - canon.position.x);
    Left += (left_z - canon.position.z) * (left_z - canon.position.z);

    Left -= 9;

    if (Left < 0 and left_y <= -3.9) {
        left_in = true;
    }

    float Right = (right_x - canon.position.x) * (right_x - canon.position.x);
    Right += (right_z - canon.position.z) * (right_z - canon.position.z);

    Right -= 9;

    if (Right < 0 and right_y <= -3.9) {
        right_in = true;
    }

    if (left_in or right_in) {
        return true;
    }
    else {
        return false;
    }
}

bool Missile::ParachuteCollision(Parachute parachute) {
    float left_x = this->left_position.x + 1.5 * cos(this->pitch * M_PI / 180) * cos(this->yaw * M_PI / 180);
    float left_y = this->left_position.y - 0.25f * sin(this->yaw * M_PI / 180);
    float left_z = this->left_position.z + 2.0f;

    float right_x = this->right_position.x + 1.5 * cos(this->pitch * M_PI / 180) * cos(this->yaw * M_PI / 180);
    float right_y = this->right_position.y - 0.25f * sin(this->yaw * M_PI / 180);
    float right_z = this->right_position.z - 2.0f;

    bool left_in;
    bool right_in;

    if ((left_x - (parachute.position.x + 2) * (left_x - (parachute.position.x - 2))) < 0) {
        if ((left_y - (parachute.position.y + 2) * (left_y - (parachute.position.y - 2))) < 0) {
            if ((left_z - (parachute.position.z + 2) * (left_z - (parachute.position.z - 2))) < 0) {
                left_in = true;
            }
            else {
                left_in = false;
            }
        }
        else {
            left_in = false;
        }
    }
    else {
        left_in = false;
    }

    if ((right_x - (parachute.position.x + 2) * (right_x - (parachute.position.x - 2))) < 0) {
        if ((right_y - (parachute.position.y + 2) * (right_y - (parachute.position.y - 2))) < 0) {
            if ((right_z - (parachute.position.z + 2) * (right_z - (parachute.position.z - 2))) < 0) {
                right_in = true;
            }
            else {
                right_in = false;
            }
        }
        else {
            right_in = false;
        }
    }
    else {
        right_in = false;
    }

    if (left_in || right_in) {
        return true;
    }
    else {
        return false;
    }
}