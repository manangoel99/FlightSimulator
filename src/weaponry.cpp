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

    if (z <= 0 and this->position.y - 2 <= 0.1) {
        return true;
    }
    else {
        return false;
    }
}