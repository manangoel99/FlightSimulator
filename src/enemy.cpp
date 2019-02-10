#include "main.h"
#include "enemy.h"

#define ll long long

SmokeRing::SmokeRing(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    GLfloat vertex_buffer_data[20000];

    ll n = 1000;

    this->radius = 3;

    float theta = 0;

    for (ll i = 0; i < 18 * n; i += 18) {
        vertex_buffer_data[i] = 0;
        vertex_buffer_data[i + 1] = this->radius * cos(theta);
        vertex_buffer_data[i + 2] = this->radius * sin(theta);
        
        vertex_buffer_data[i + 3] = 0;
        vertex_buffer_data[i + 4] = this->radius * cos(theta) + 0.1;
        vertex_buffer_data[i + 5] = this->radius * sin(theta);
        
        vertex_buffer_data[i + 6] = 0;
        vertex_buffer_data[i + 7] = this->radius * cos(theta + (2 * M_PI / n));
        vertex_buffer_data[i + 8] = this->radius * sin(theta + (2 * M_PI / n));
        
        vertex_buffer_data[i + 9] = 0;
        vertex_buffer_data[i + 10] = this->radius * cos(theta) + 0.1;
        vertex_buffer_data[i + 11] = this->radius * sin(theta);

        vertex_buffer_data[i + 12] = 0;
        vertex_buffer_data[i + 13] = this->radius * cos(theta + (2 * M_PI / n)) + 0.1;
        vertex_buffer_data[i + 14] = this->radius * sin(theta + (2 * M_PI / n)) + 0.1;

        vertex_buffer_data[i + 15] = 0;
        vertex_buffer_data[i + 16] = this->radius * cos(theta + (2 * M_PI / n));
        vertex_buffer_data[i + 17] = this->radius * sin(theta + (2 * M_PI / n));

        theta += (2 * M_PI) / n;
    }

    this->color = COLOR_GREY;

    this->object = create3DObject(GL_TRIANGLES, 6 * n, vertex_buffer_data, this->color, GL_FILL);
    

}

void SmokeRing::draw(glm::mat4 VP) {
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