#include "main.h"
#include "enemy.h"
#include "plane.h"

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

bool SmokeRing::DetectPassing(Plane plane) {
    float dist = (this->position.x - plane.position.x) * (this->position.x - plane.position.x);
    dist += (this->position.y - plane.position.y) * (this->position.y - plane.position.y);
    dist += (this->position.z - plane.position.z) * (this->position.z - plane.position.z);

    if (dist <= this->radius * this->radius) {
        if ((plane.position.x - 2 < this->position.x && plane.position.x + 2 > this->position.x) || (plane.position.x - 2 > this->position.x && plane.position.x + 2 < this->position.x)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }

}

Volcano::Volcano(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);

    ll n = 1000;

    GLfloat vertex_buffer_data[100000];
    float theta = 0;

    this->height = (rand() % 4) + 1;

    this->UpperRadius = (rand() % 3) + 1;
    this->LowerRadius = this->UpperRadius + 3;

    for (ll i = 0; i < 18 * n; i += 18) {
        vertex_buffer_data[i] = this->LowerRadius * cos(theta);
        vertex_buffer_data[i + 1] = 0;
        vertex_buffer_data[i + 2] = this->LowerRadius * sin(theta);

        vertex_buffer_data[i + 3] = this->LowerRadius * cos(theta + (2 * M_PI / n));
        vertex_buffer_data[i + 4] = 0;
        vertex_buffer_data[i + 5] = this->LowerRadius * sin(theta + +(2 * M_PI / n));

        vertex_buffer_data[i + 6] = this->UpperRadius * cos(theta);
        vertex_buffer_data[i + 7] = this->height;
        vertex_buffer_data[i + 8] = this->UpperRadius * sin(theta);

        vertex_buffer_data[i + 9] = this->LowerRadius * cos(theta + (2 * M_PI / n));
        vertex_buffer_data[i + 10] = 0;
        vertex_buffer_data[i + 11] = this->LowerRadius * sin(theta + (2 * M_PI / n));

        vertex_buffer_data[i + 12] = this->UpperRadius * cos(theta + (2 * M_PI / n));
        vertex_buffer_data[i + 13] = this->height;
        vertex_buffer_data[i + 14] = this->UpperRadius * sin(theta + +(2 * M_PI / n));

        vertex_buffer_data[i + 15] = this->UpperRadius * cos(theta);
        vertex_buffer_data[i + 16] = this->height;
        vertex_buffer_data[i + 17] = this->UpperRadius * sin(theta);

        theta += (2 * M_PI) / n;
    }

    this->object = create3DObject(GL_TRIANGLES, 6 * n, vertex_buffer_data, COLOR_BROWN, GL_FILL);
    
    theta = 0;

    GLfloat secon_arr[10000];

    for (ll i = 0; i < 9 * n; i += 9) {
        secon_arr[i] = 0;
        secon_arr[i + 1] = this->height;
        secon_arr[i + 2] = 0;

        secon_arr[i + 3] = this->UpperRadius * sin(theta);
        secon_arr[i + 4] = this->height;
        secon_arr[i + 5] = this->UpperRadius * cos(theta);

        secon_arr[i + 6] = this->UpperRadius * sin(theta + (2 * M_PI / n));
        secon_arr[i + 7] = this->height;
        secon_arr[i + 8] = this->UpperRadius * cos(theta + (2 * M_PI / n));

        theta += (2 * M_PI) / n;
    }

    this->TopDisc = create3DObject(GL_TRIANGLES, 3 * n, secon_arr, COLOR_RED, GL_FILL);

}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->TopDisc);
}