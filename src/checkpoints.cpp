#include "main.h"
#include "checkpoints.h"
#include <glm/gtx/vector_angle.hpp>

CheckPoint::CheckPoint(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);

    GLfloat vertex_buffer_data[] = {
        0, -3.5f, 3.5f,
        0, -3.0f, 3.0f,
        0, 3.5f, 3.5f,

        0, -3.0f, 3.0f,
        0, 3.5f, 3.5f,
        0, 3.0f, 3.0f,

        0.0f, 3.5f, 3.5f,
        0.0f, 3.0f, 3.0f,
        0.0f, 3.5f, -3.5f,

        0.0f, 3.0f, -3.0f,
        0.0f, 3.0f, 3.0f,
        0.0f, 3.5f, -3.5f,

        0, -3.5f, -3.5f,
        0, -3.0f, -3.0f,
        0, 3.5f, -3.5f,

        0, -3.0f, -3.0f,
        0, 3.5f, -3.5f,
        0, 3.0f, -3.0f,

        0.0f, -3.5f, 3.5f,
        0.0f, -3.0f, 3.0f,
        0.0f, -3.5f, -3.5f,

        0.0f, -3.0f, -3.0f,
        0.0f, -3.0f, 3.0f,
        0.0f, -3.5f, -3.5f,

    };

    this->COLOR = {
        255, 215, 0,
    };

    this->rotation = 0;

    this->object = create3DObject(GL_TRIANGLES, 24, vertex_buffer_data, this->COLOR, GL_FILL);
}

void CheckPoint::draw(glm::mat4 VP) {
    this->rotation += 1;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bool CheckPoint::DetectPassing(Plane plane) {
    float y_in;
    float z_in;
    float x_in;
    y_in = (plane.position.y - (this->position.y - 3)) * (plane.position.y - (this->position.y + 3));
    z_in = (plane.position.z - (this->position.z - 3)) * (plane.position.z - (this->position.z + 3));
    x_in = (plane.position.x - (this->position.x - 0.1)) * (plane.position.x - (this->position.x + 0.1));

    if (y_in < 0 and x_in < 0 and z_in < 0) {
        return true;
    }
    else {
        return false;
    }

}

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);

    long long n = 1000;

    float radius = 0.125;

    GLfloat main_buffer[10000];
    GLfloat tail_buffer[10000];

    this->pitch = 0;
    this->yaw = 0;

    float theta = 0;

    for (long long i = 0; i < 9 * n; i += 9) {
        main_buffer[i + 0] = radius * cos(theta);
        main_buffer[i + 1] = radius * sin(theta);
        main_buffer[i + 2] = 0.5;

        main_buffer[i + 3] = 0;
        main_buffer[i + 4] = 0;
        main_buffer[i + 5] = 0.75;

        main_buffer[i + 6] = radius * cos(theta + (2 * M_PI / n));
        main_buffer[i + 7] = radius * sin(theta + (2 * M_PI / n));
        main_buffer[i + 8] = 0.5;

        theta += (2 * M_PI / n);
    }

    radius = 0.0625f;
    theta = 0;

    for (long long i = 0; i < 9 * n; i += 9) {
        tail_buffer[i + 0] = radius * cos(theta);
        tail_buffer[i + 1] = radius * sin(theta);
        tail_buffer[i + 2] = 0;

        tail_buffer[i + 3] = 0;
        tail_buffer[i + 4] = 0;
        tail_buffer[i + 5] = 0.5;

        tail_buffer[i + 6] = radius * cos(theta + (2 * M_PI / n));
        tail_buffer[i + 7] = radius * sin(theta + (2 * M_PI / n));
        tail_buffer[i + 8] = 0;

        theta += (2 * M_PI / n);
    }

    this->MainObject = create3DObject(GL_TRIANGLES, 3 * n, main_buffer, COLOR_RED, GL_FILL);
    this->TailObject = create3DObject(GL_TRIANGLES, 3 * n, tail_buffer, COLOR_BROWN, GL_FILL);
}

void Arrow::draw(glm::mat4 VP, Plane plane, CheckPoint c) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    //glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));

    glm::vec3 vec = plane.position - c.position;

    this->pitch = M_PI + atan2(vec.x, vec.z);
    this->yaw = atan2(vec.y, sqrt(vec.x * vec.x + vec.z * vec.z));

    glm::mat4 rotate_yaw = glm::rotate(this->yaw, glm::vec3(sin(plane.pitch * M_PI / 180), 0, cos(plane.pitch * M_PI / 180)));
    glm::mat4 rotate_pitch = glm::rotate(this->pitch, glm::vec3(0, 1, 0));

    Matrices.model *= translate * rotate_yaw * rotate_pitch;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->MainObject);
    draw3DObject(this->TailObject);
}