#include "main.h"
#include "plane.h"

#define ll long long

Plane::Plane(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    
    this->speed = glm::vec3(0, 0, 0);

    ll n = 1000;
    GLfloat coord[200000];
    float r = 1.0f;
    this->rotation = 0;
    this->roll = 0;
    this->pitch = 0;
    this->yaw = 0;
    this->life = 40;

    float theta = 0;

    for (ll i = 0; i < 9 * n; i += 9)
    {
        coord[i] = 2;
        coord[i + 1] = r * sin(theta);
        coord[i + 2] = r * cos(theta);
        coord[i + 3] = 3;
        coord[i + 4] = 0;
        coord[i + 5] = 0;
        coord[i + 6] = 2;
        coord[i + 7] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 8] = r * cos(theta + (2 * M_PI) / n);

        theta += ((2 * M_PI) / n);
    }

    theta = 0;

    for(ll i = 9 * n; i < 27 * n; i += 18)
    {
        coord[i] = 0;
        coord[i + 1] = r * sin(theta);
        coord[i + 2] = r * cos(theta);

        coord[i + 3] = 2;
        coord[i + 4] = r * sin(theta);
        coord[i + 5] = r * cos(theta);

        coord[i + 6] = 0;
        coord[i + 7] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 8] = r * cos(theta + (2 * M_PI) / n);

        coord[i + 9] = 0;
        coord[i + 10] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 11] = r * cos(theta + (2 * M_PI) / n);

        coord[i + 12] = 2;
        coord[i + 13] = r * sin(theta);
        coord[i + 14] = r * cos(theta);

        coord[i + 15] = 2;
        coord[i + 16] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 17] = r * cos(theta + (2 * M_PI) / n);

        theta += ((2 * M_PI) / n);
    }

    theta = 0;

    for (ll i = 27 * n; i < 45 * n; i += 18)
    {
        coord[i] = 0;
        coord[i + 1] = r * sin(theta);
        coord[i + 2] = r * cos(theta);

        coord[i + 3] = -2;
        coord[i + 4] = r * sin(theta);
        coord[i + 5] = r * cos(theta);

        coord[i + 6] = 0;
        coord[i + 7] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 8] = r * cos(theta + (2 * M_PI) / n);

        coord[i + 9] = 0;
        coord[i + 10] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 11] = r * cos(theta + (2 * M_PI) / n);

        coord[i + 12] = -2;
        coord[i + 13] = r * sin(theta);
        coord[i + 14] = r * cos(theta);

        coord[i + 15] = -2;
        coord[i + 16] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 17] = r * cos(theta + (2 * M_PI) / n);

        theta += ((2 * M_PI) / n);
    }
    
    GLfloat coord_fin[] = {
        -2.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -2.0f, 2.0f, 0.0f,
    };

    GLfloat coord_wing[] = {
        -0.25f, 0.0f, 1.0f,
        0.75f, 0.0f, 1.0f,
        -0.25f, 0.0f, 3.0f,
        -0.25f, 0.0f, -1.0f,
        0.75f, 0.0f, -1.0f,
        -0.25f, 0.0f, -3.0f,
        -2.0f, 0.0f, 1.0f,
        -2.0f, 0.0f, 1.5f,
        -1.5f, 0.0f, 1.0f,
        -2.0f, 0.0f, -1.0f,
        -2.0f, 0.0f, -1.5f,
        -1.5f, 0.0f, -1.0f,

    };

    GLfloat left_coord_missile[50000];
    GLfloat right_coord_missile[50000];
    theta = 0;

    r = 0.25f;

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

        theta += ((2 * M_PI) / n);
    }

    theta = 0;

    for(ll i = 9 * n; i < 27 * n; i += 18)
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

        theta += ((2 * M_PI) / n);
    }

    for (ll i = 0; i < 45 * n; i++) {
        if (i % 3 == 2) {
            left_coord_missile[i] += 2.0f;
        }
        if (i % 3 == 1) {
            left_coord_missile[i] -= 0.25f;
        }
    }

    for (ll i = 0; i < 9 * n; i += 9)
    {
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

    for(ll i = 9 * n; i < 27 * n; i += 18)
    {
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
            right_coord_missile[i] -= 2.0f;
        }
        if (i % 3 == 1) {
            right_coord_missile[i] -= 0.25f;
        }
    }

    this->object = create3DObject(GL_TRIANGLES, 15 * n + 3, coord, color, GL_FILL);
    this->finobj = create3DObject(GL_TRIANGLES, 3, coord_fin, COLOR_GREEN, GL_FILL);
    this->wingobj = create3DObject(GL_TRIANGLES, 12, coord_wing, COLOR_GREEN, GL_FILL);
    this->leftmissileobj = create3DObject(GL_TRIANGLES, 15 * n + 3, left_coord_missile, COLOR_BROWN, GL_FILL);
    this->rightmissileobj = create3DObject(GL_TRIANGLES, 15 * n + 3, right_coord_missile, COLOR_BROWN, GL_FILL);
} 

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 mat_pitch = glm::rotate((float)(this->pitch * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 mat_roll = glm::rotate((float)(this->roll * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 mat_yaw = glm::rotate((float)(this->yaw * M_PI / 180.0f), glm::vec3(sin(M_PI * this->pitch / 180), 0, cos(M_PI * this->pitch / 180)));
    //std::cout << this->pitch << '\t' << sin(this->pitch * M_PI / 180) << '\t' << cos(this->pitch * M_PI / 180) << std::endl;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * mat_yaw * mat_pitch * mat_roll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->finobj);
    draw3DObject(this->wingobj);
    draw3DObject(this->leftmissileobj);
    draw3DObject(this->rightmissileobj);
}

void Plane::tick() {
    //this->position += this->speed;
}