#include "main.h"
#include "dashboard.h"
#define ll long long

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

Compass::Compass (float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    ll n = 1000;

    this->radius = 1.5f;

    float theta = 0;

    GLfloat vertex_buffer_data[20000];

    for (ll i = 0; i < 18 * n; i += 18) {
        vertex_buffer_data[i + 2] = 0;
        vertex_buffer_data[i + 1] = this->radius * cos(theta);
        vertex_buffer_data[i + 0] = this->radius * sin(theta);
        
        vertex_buffer_data[i + 5] = 0;
        vertex_buffer_data[i + 4] = this->radius * cos(theta) + 0.2;
        vertex_buffer_data[i + 3] = this->radius * sin(theta);
        
        vertex_buffer_data[i + 8] = 0;
        vertex_buffer_data[i + 7] = this->radius * cos(theta + (2 * M_PI / n));
        vertex_buffer_data[i + 6] = this->radius * sin(theta + (2 * M_PI / n));
        
        vertex_buffer_data[i + 11] = 0;
        vertex_buffer_data[i + 10] = this->radius * cos(theta) + 0.2;
        vertex_buffer_data[i + 9] = this->radius * sin(theta);

        vertex_buffer_data[i + 14] = 0;
        vertex_buffer_data[i + 13] = this->radius * cos(theta + (2 * M_PI / n)) + 0.2;
        vertex_buffer_data[i + 12] = this->radius * sin(theta + (2 * M_PI / n)) + 0.2;

        vertex_buffer_data[i + 17] = 0;
        vertex_buffer_data[i + 16] = this->radius * cos(theta + (2 * M_PI / n));
        vertex_buffer_data[i + 15] = this->radius * sin(theta + (2 * M_PI / n));

        theta += (2 * M_PI) / n;
    }

    GLfloat needle_buffer_data[] = {
        -0.1f, 0.0f, 0.0f,
        0.1f, 0.0f, 0.0f,
        0.0f, 1.5f, 0.0f,
    };


    this->base = create3DObject(GL_TRIANGLES, 6 * n, vertex_buffer_data, COLOR_GREY, GL_FILL);
    this->Direction = create3DObject(GL_TRIANGLES, 3, needle_buffer_data, COLOR_BLACK, GL_FILL);
    this->northNeedle = create3DObject(GL_TRIANGLES, 3, needle_buffer_data, COLOR_RED, GL_FILL);
}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->plane_rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);//* rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base);
    draw3DObject(this->Direction);

    Matrices.model *= rotate;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->northNeedle);
}

void Compass::set_rotation(Plane plane) {
    this->plane_rotation = -plane.pitch;
}

FuelGauge::FuelGauge(float x, float y, float z, Plane plane) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->fuel = plane.fuel;

    static const GLfloat vertec_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        2.0f, 0.0f, 0.0f,
        2.0f, 0.4f, 0.0f,

        0.0f, 0.0f, 0.0f,
        0.0f, 0.4f, 0.0f,
        2.0f, 0.4f, 0.0f,
    };

    color_t COLOR_VIOLET = {
        238, 130, 238
    };

    this->MainObject = create3DObject(GL_TRIANGLES, 6, vertec_buffer_data, COLOR_BLACK, GL_FILL);
    this->FuelObject = create3DObject(GL_TRIANGLES, 6, vertec_buffer_data, COLOR_VIOLET, GL_FILL);
}

void FuelGauge::set_fuel(Plane plane) {
    float height = (float) (plane.fuel) / (float) 100;
//
    //cout << plane.fuel << endl;
    //GLfloat Life = (GLfloat)plane.life / (GLfloat)40;

    GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        2 * height, 0.0f, 0.0f,
        2 * height, 0.4f, 0.0f,

        0.0f, 0.0f, 0.0f,
        0.0f, 0.4f, 0.0f,
        2 * height, 0.4f, 0.0f,
    };

    if (height <= -0.2) {
        this->FuelObject = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_RED, GL_FILL);
    }
    else {
        this->FuelObject = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_BLUE, GL_FILL);
    }
}

void FuelGauge::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->MainObject);
    draw3DObject(this->FuelObject);
}