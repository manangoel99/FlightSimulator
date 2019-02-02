#include "main.h"
#include "plane.h"

#define ll long long

Plane::Plane(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    

    ll n = 1000;
    GLfloat coord[200000];
    float r = 1.0f;
    this->rotation = 0;

    float theta = 0;

    for (ll i = 0; i < 9 * n; i += 9)
    {
        coord[i] = 1;
        coord[i + 1] = r * sin(theta);
        coord[i + 2] = r * cos(theta);
        coord[i + 3] = 2;
        coord[i + 4] = 0;
        coord[i + 5] = 0;
        coord[i + 6] = 1;
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

        coord[i + 3] = 1;
        coord[i + 4] = r * sin(theta);
        coord[i + 5] = r * cos(theta);

        coord[i + 6] = 0;
        coord[i + 7] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 8] = r * cos(theta + (2 * M_PI) / n);

        coord[i + 9] = 0;
        coord[i + 10] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 11] = r * cos(theta + (2 * M_PI) / n);

        coord[i + 12] = 1;
        coord[i + 13] = r * sin(theta);
        coord[i + 14] = r * cos(theta);

        coord[i + 15] = 1;
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

        coord[i + 3] = -1;
        coord[i + 4] = r * sin(theta);
        coord[i + 5] = r * cos(theta);

        coord[i + 6] = 0;
        coord[i + 7] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 8] = r * cos(theta + (2 * M_PI) / n);

        coord[i + 9] = 0;
        coord[i + 10] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 11] = r * cos(theta + (2 * M_PI) / n);

        coord[i + 12] = -1;
        coord[i + 13] = r * sin(theta);
        coord[i + 14] = r * cos(theta);

        coord[i + 15] = -1;
        coord[i + 16] = r * sin(theta + (2 * M_PI) / n);
        coord[i + 17] = r * cos(theta + (2 * M_PI) / n);

        theta += ((2 * M_PI) / n);
    }
    
    GLfloat coord_fin[] = {
        -1.0f, 1.0f, 0.0f,
        -0.5f, 1.0f, 0.0f,
        -1.0f, 2.0f, 0.0f,
    };

    //for (ll i = 45 * n; i < 54 * n; i += 9)
    //{
    //    coord[i] = -1;
    //    coord[i + 1] = r * sin(theta);
    //    coord[i + 2] = r * cos(theta);
    //    coord[i + 3] = -1.5;
    //    coord[i + 4] = 0;
    //    coord[i + 5] = 0;
    //    coord[i + 6] = -1;
    //    coord[i + 7] = r * sin(theta + (2 * M_PI) / n);
    //    coord[i + 8] = r * cos(theta + (2 * M_PI) / n);
//
    //    theta += ((2 * M_PI) / n);
    //}

    GLfloat coord_wing[] = {
        -0.5f, 0.0f, 1.0f,
        0.5f, 0.0f, 1.0f,
        -0.5f, 0.0f, 3.0f,
        -0.5f, 0.0f, -1.0f,
        0.5f, 0.0f, -1.0f,
        -0.5f, 0.0f, -3.0f,

    }; 
    //coord[54 * n] = -1.0f;
    //coord[54 * n + 1] = 1.0f;
    //coord[54 * n + 2] = 0.0f;//

    //coord[54 * n + 3] = -0.75f;
    //coord[54 * n + 4] = 1.0f;
    //coord[54 * n + 5] = 0.0f;//

    //coord[54 * n + 6] = -1.0f;
    //coord[54 * n + 7] = 1.25f;
    //coord[54 * n + 8] = 0.0f;

    this->object = create3DObject(GL_TRIANGLES, 15 * n + 3, coord, color, GL_FILL);
    this->finobj = create3DObject(GL_TRIANGLES, 3, coord_fin, COLOR_GREEN, GL_FILL);
    this->wingobj = create3DObject(GL_TRIANGLES, 6, coord_wing, COLOR_GREEN, GL_FILL);
} 

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->finobj);
    draw3DObject(this->wingobj);
}