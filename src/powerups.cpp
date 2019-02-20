#include "main.h"
#include "powerups.h"

LifePowerUp::LifePowerUp (float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->COLOR = {
        212, 175, 55
    };
    this->rotation = 0;

    GLfloat vertex_buffer_data[] = {
        -0.5f,-0.5f,-0.5f, // triangle 1 : begin
        -0.5f,-0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f, // triangle 1 : end
        0.5f, 0.5f,-0.5f, // triangle 2 : begin
        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f, // triangle 2 : end
        0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f, 0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f,
        0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,
        0.5f,-0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f, 0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f,-0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f,-0.5f, 0.5f
    };

    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, this->COLOR, GL_FILL);

}

void LifePowerUp::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bool LifePowerUp::CheckCollision(Plane plane) {
    glm::vec3 b = glm::vec3 (plane.position.x + 3 * cos(plane.pitch * M_PI / 180), plane.position.y, plane.position.z - 3 * sin(plane.pitch * M_PI / 180));
    glm::vec3 c = plane.position;
    glm::vec3 a = this->position;

    glm::vec3 d = (c - b) / glm::distance(c, b);
    glm::vec3 v = a - b;

    double t = glm::dot(v, d);

    glm::vec3 p = b + glm::vec3(t * d.x, t * d.y, t * d.z);
    double dist = glm::distance(p, a);

    if (dist <= 1 && ((this->position.x - (plane.position.x + 3)) * (this->position.x - (plane.position.x - 2)) < 0)) {
        return true;
    }
    else {
        return false;
    }
}

FuelPowerUp::FuelPowerUp (float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->COLOR = {
        142, 68, 173
    };
    this->rotation = 0;

    GLfloat vertex_buffer_data[] = {
        -0.5f,-0.5f,-0.5f, // triangle 1 : begin
        -0.5f,-0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f, // triangle 1 : end
        0.5f, 0.5f,-0.5f, // triangle 2 : begin
        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f, // triangle 2 : end
        0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f, 0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f,
        0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,
        0.5f,-0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f, 0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f,-0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f,-0.5f, 0.5f
    };

    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, this->COLOR, GL_FILL);

}

void FuelPowerUp::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bool FuelPowerUp::CheckCollision(Plane plane) {

    this->rotation += 1;
    glm::vec3 b = glm::vec3 (plane.position.x + 3 * cos(plane.pitch * M_PI / 180), plane.position.y, plane.position.z - 3 * sin(plane.pitch * M_PI / 180));
    glm::vec3 c = plane.position;
    glm::vec3 a = this->position;

    glm::vec3 d = (c - b) / glm::distance(c, b);
    glm::vec3 v = a - b;

    double t = glm::dot(v, d);

    glm::vec3 p = b + glm::vec3(t * d.x, t * d.y, t * d.z);
    double dist = glm::distance(p, a);

    if (dist <= 1 && ((this->position.x - (plane.position.x + 3)) * (this->position.x - (plane.position.x - 2)) < 0)) {
        return true;
    }
    else {
        return false;
    }
}