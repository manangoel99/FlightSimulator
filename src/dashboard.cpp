#include "main.h"
#include "dashboard.h"

using namespace std;

LifeBar::LifeBar(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    float rotation = 0;

    static const GLfloat vertec_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        2.0f, 0.0f, 0.0f,
        2.0f, 0.4f, 0.0f,

        0.0f, 0.0f, 0.0f,
        0.0f, 0.4f, 0.0f,
        2.0f, 0.4f, 0.0f,
    };

    this->TotalObject = create3DObject(GL_TRIANGLES, 6, vertec_buffer_data, COLOR_BLACK, GL_FILL);

}

void LifeBar::CreateLifeObject(Plane plane) {
    GLfloat Life = (GLfloat)plane.life / (GLfloat)40;

    GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        2 * Life, 0.0f, 0.0f,
        2 * Life, 0.4f, 0.0f,

        0.0f, 0.0f, 0.0f,
        0.0f, 0.4f, 0.0f,
        2 * Life, 0.4f, 0.0f,
    };

    this->LifeObject = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_GREEN, GL_FILL);
}

void LifeBar::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->TotalObject);
    draw3DObject(this->LifeObject);
}

HeightBar::HeightBar(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    static const GLfloat vertec_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        2.0f, 0.0f, 0.0f,
        2.0f, 0.4f, 0.0f,

        0.0f, 0.0f, 0.0f,
        0.0f, 0.4f, 0.0f,
        2.0f, 0.4f, 0.0f,
    };

    this->TotalObject = create3DObject(GL_TRIANGLES, 6, vertec_buffer_data, COLOR_BLACK, GL_FILL);


}

void HeightBar::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->TotalObject);
    draw3DObject(this->HeightObject);
}

void HeightBar::UpdateBar(Plane plane) {
    float height = (float) (plane.position.y - 20.0) / (float) 100;

    GLfloat vertex_buffer_data[] = {
        0.24f, 0.0f, 0.0f,
        0.24f, 0.4f, 0.0f,
        0.24f + height, 0.0f, 0.0f,

        0.24f + height, 0.4f, 0.0f,
        0.24f + height, 0.0f, 0.0f,
        0.24f, 0.4f, 0.0f,
    };

    if (height <= -0.2) {
        this->HeightObject = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_RED, GL_FILL);
    }
    else {
        this->HeightObject = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_BLUE, GL_FILL);
    }
}