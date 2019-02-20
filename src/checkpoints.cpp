#include "main.h"
#include "checkpoints.h"

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