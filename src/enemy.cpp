#include "main.h"
#include "enemy.h"
#include "plane.h"

#define ll long long

using namespace std;

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

bool Volcano::DetectPassing(Plane plane) {
    float dist = (plane.position.x + 2 - this->position.x) * (plane.position.x + 2 - this->position.x);
    dist += (plane.position.z - this->position.z) * (plane.position.z - this->position.z);

    if (dist * dist <= this->UpperRadius * this->UpperRadius) {
        return true;
    }
    else {
        return false;
    }
}

Canon::Canon (float x, float y, float z) {
    this->position = glm::vec3(x, y, z);

    GLfloat coord[36000];

    float theta = 0;

    ll n = 1000;

    float r = 0.25;

    for (ll i = 0 * n; i < 18 * n; i += 18)
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

    for (ll i = 18 * n; i < 36 * n; i += 18)
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

    GLfloat second_arr[10000];

    theta = 0;

    n = 1000;

    r = 3;

    for (ll i = 0; i < 9 * n; i += 9) {
        second_arr[i] = r * cos(theta);
        second_arr[i + 1] = 0.1;
        second_arr[i + 2] = r * sin(theta);

        second_arr[i + 3] = 0;
        second_arr[i + 4] = 0.1;
        second_arr[i + 5] = 0;

        second_arr[i + 6] = r * cos(theta + (2 * M_PI / n));
        second_arr[i + 7] = 0.1;
        second_arr[i + 8] = r * sin(theta + (2 * M_PI / n));

        theta += (2 * M_PI / n);
    }


    this->object = create3DObject(GL_TRIANGLES, 12 * n, coord, COLOR_BLACK, GL_FILL);
    this->disc = create3DObject(GL_TRIANGLES, 3 * n, second_arr, COLOR_GREY, GL_FILL);
}

void Canon::draw(glm::mat4 VP, glm::vec3 planevec) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    
    float angle1 = atan2(planevec.y, planevec.x);
    
    glm::mat4 rotate1 = glm::rotate(angle1, glm::vec3(0, 0, 1));

    float angle2 = atan2(planevec.z, sqrt(planevec.x * planevec.x + planevec.y * planevec.y));

    glm::mat4 rotate2 = glm::rotate(angle2, glm::vec3(asin(planevec.y / sqrt(planevec.y * planevec.y + planevec.x * planevec.x)), -1 * acos(planevec.x / sqrt(planevec.y * planevec.y + planevec.x * planevec.x)), 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate2 * rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Canon::drawdisc(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));

    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->disc);
}

bool CanonBall::detect_collision(Plane plane) {
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

CanonBall::CanonBall(float x, float y, float z, glm::vec3 planevec) {
    this->position = glm::vec3(x, y, z);
    this->velocity = glm::vec3(planevec.x / 15, planevec.y / 15, planevec.z / 15);
    this->rotation = 0;

    this->acc = glm::vec3(0, -0.0125, 0);

    static const GLfloat vertex_buffer_data[] = {
        -0.4f,-0.4f,-0.4f, // triangle 1 : begin
        -0.4f,-0.4f, 0.4f,
        -0.4f, 0.4f, 0.4f, // triangle 1 : end
        0.4f, 0.4f,-0.4f, // triangle 2 : begin
        -0.4f,-0.4f,-0.4f,
        -0.4f, 0.4f,-0.4f, // triangle 2 : end
        0.4f,-0.4f, 0.4f,
        -0.4f,-0.4f,-0.4f,
        0.4f,-0.4f,-0.4f,
        0.4f, 0.4f,-0.4f,
        0.4f,-0.4f,-0.4f,
        -0.4f,-0.4f,-0.4f,
        -0.4f,-0.4f,-0.4f,
        -0.4f, 0.4f, 0.4f,
        -0.4f, 0.4f,-0.4f,
        0.4f,-0.4f, 0.4f,
        -0.4f,-0.4f, 0.4f,
        -0.4f,-0.4f,-0.4f,
        -0.4f, 0.4f, 0.4f,
        -0.4f,-0.4f, 0.4f,
        0.4f,-0.4f, 0.4f,
        0.4f, 0.4f, 0.4f,
        0.4f,-0.4f,-0.4f,
        0.4f, 0.4f,-0.4f,
        0.4f,-0.4f,-0.4f,
        0.4f, 0.4f, 0.4f,
        0.4f,-0.4f, 0.4f,
        0.4f, 0.4f, 0.4f,
        0.4f, 0.4f,-0.4f,
        -0.4f, 0.4f,-0.4f,
        0.4f, 0.4f, 0.4f,
        -0.4f, 0.4f,-0.4f,
        -0.4f, 0.4f, 0.4f,
        0.4f, 0.4f, 0.4f,
        -0.4f, 0.4f, 0.4f,
        0.4f,-0.4f, 0.4f
    };

    
    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, COLOR_GREEN, GL_FILL);

}

void CanonBall::draw(glm::mat4 VP) {
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

void CanonBall::tick() {
    this->position += this->velocity;
    this->velocity += this->acc;
    this->rotation += 1;
}

Parachute::Parachute (float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 270;
    this->velocity = glm::vec3(0, 0, 0);
    this->acc = glm::vec3(0, -0.001, 0);

    GLfloat vertex_buffer_data[] = {
        -2.0f,-2.0f,-2.0f, // triangle 2 : begin
        -2.0f,-2.0f, 2.0f,
        -2.0f, 2.0f, 2.0f, // triangle 2 : end

        2.0f, 2.0f,-2.0f, // triangle 2 : begin
        -2.0f,-2.0f,-2.0f,
        -2.0f, 2.0f,-2.0f, // triangle 2 : end

        2.0f,-2.0f, 2.0f,
        -2.0f,-2.0f,-2.0f,
        2.0f,-2.0f,-2.0f,

        2.0f, 2.0f,-2.0f,
        2.0f,-2.0f,-2.0f,
        -2.0f,-2.0f,-2.0f,

        -2.0f,-2.0f,-2.0f,
        -2.0f, 2.0f, 2.0f,
        -2.0f, 2.0f,-2.0f,

        2.0f,-2.0f, 2.0f,
        -2.0f,-2.0f, 2.0f,
        -2.0f,-2.0f,-2.0f,

        -2.0f, 2.0f, 2.0f,
        -2.0f,-2.0f, 2.0f,
        2.0f,-2.0f, 2.0f,

        2.0f, 2.0f, 2.0f,
        2.0f,-2.0f,-2.0f,
        2.0f, 2.0f,-2.0f,

        2.0f,-2.0f,-2.0f,
        2.0f, 2.0f, 2.0f,
        2.0f,-2.0f, 2.0f,

        2.0f, 2.0f, 2.0f,
        2.0f, 2.0f,-2.0f,
        -2.0f, 2.0f,-2.0f,

        2.0f, 2.0f, 2.0f,
        -2.0f, 2.0f,-2.0f,
        -2.0f, 2.0f, 2.0f,

        2.0f, 2.0f, 2.0f,
        -2.0f, 2.0f, 2.0f,
        2.0f,-2.0f, 2.0f
    };

    GLfloat parachute_arr[540000] = {-1};

    color_t COLOR_JADEGREEN = {
        0, 168, 107,
    };

    float radius = 4.0f;

    int sides = 100;
    float angle = (2 * M_PI) / float(sides);

    for(ll i = 0; i < sides / 2; i++)
        for(ll j = 0; j < sides; j++)
        {
            int k = sides * i + j;
            parachute_arr[9 * k] = 0.0f;
            parachute_arr[9 * k + 1] = 0.0f;  
            parachute_arr[9 * k + 2] = 4 + radius * sin(i * angle);

            parachute_arr[9 * k + 3] = radius * cos(j * angle) * cos(i * angle); 
            parachute_arr[9 * k + 4] = radius * sin(j * angle) * cos(i * angle);
            parachute_arr[9 * k + 5] = 4 + radius * sin(i * angle); 

            parachute_arr[9 * k + 6] = radius * cos((j + 1) * angle) * cos(i * angle); 
            parachute_arr[9 * k + 7] = radius * sin((j + 1) * angle) * cos(i * angle); 
            parachute_arr[9 * k + 8] = 4 + radius * sin(i * angle); 
        }
    
    this->ParachuteObject = create3DObject(GL_TRIANGLES, sides*sides*3, parachute_arr, COLOR_JADEGREEN, GL_FILL);

    GLfloat vertex_buffer[] = {
        2.0f, 2.0f, 2.0f,
        radius * cos (M_PI / 4), radius * sin (M_PI / 4), 4.0f,
        radius * cos((M_PI / 4) + angle), radius * sin((M_PI / 4) + angle), 4.0f,

        -2.0f, 2.0f, 2.0f,
        radius * cos (3 * M_PI / 4), radius * sin (3 * M_PI / 4), 4.0f,
        radius * cos((3 * M_PI / 4) + angle), radius * sin((3 * M_PI / 4) + angle), 4.0f,

        -2.0f, -2.0f, 2.0f,
        radius * cos (5 * M_PI / 4), radius * sin (5 * M_PI / 4), 4.0f,
        radius * cos((5 * M_PI / 4) + angle), radius * sin((5 * M_PI / 4) + angle), 4.0f,

        2.0f, -2.0f, 2.0f,
        radius * cos (7 * M_PI / 4), radius * sin (7 * M_PI / 4), 4.0f,
        radius * cos((7 * M_PI / 4) + angle), radius * sin((7 * M_PI / 4) + angle), 4.0f,
    };

    this->RopeObject = create3DObject(GL_TRIANGLES, 12, vertex_buffer, COLOR_BLACK, GL_FILL);

    this->MainObject = create3DObject(GL_TRIANGLES, 12 * 3, vertex_buffer_data, COLOR_JADEGREEN, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->MainObject);
    draw3DObject(this->ParachuteObject);
    draw3DObject(this->RopeObject);
}

void Parachute::tick() {
    this->position += this->velocity;
    this->velocity += this->acc;
}

Bullet::Bullet(float x, float y, float z, glm::vec3 planevec) {
    this->position = glm::vec3(x, y, z);
    this->velocity = glm::vec3(planevec.x / 15, planevec.y / 15, planevec.z / 15);
    this->rotation = 0;

    this->acc = glm::vec3(0, -0.0125, 0);

    static const GLfloat vertex_buffer_data[] = {
        -0.25f,-0.25f,-0.25f, // triangle 1 : begin
        -0.25f,-0.25f, 0.25f,
        -0.25f, 0.25f, 0.25f, // triangle 1 : end
        0.25f, 0.25f,-0.25f, // triangle 2 : begin
        -0.25f,-0.25f,-0.25f,
        -0.25f, 0.25f,-0.25f, // triangle 2 : end
        0.25f,-0.25f, 0.25f,
        -0.25f,-0.25f,-0.25f,
        0.25f,-0.25f,-0.25f,
        0.25f, 0.25f,-0.25f,
        0.25f,-0.25f,-0.25f,
        -0.25f,-0.25f,-0.25f,
        -0.25f,-0.25f,-0.25f,
        -0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f,-0.25f,
        0.25f,-0.25f, 0.25f,
        -0.25f,-0.25f, 0.25f,
        -0.25f,-0.25f,-0.25f,
        -0.25f, 0.25f, 0.25f,
        -0.25f,-0.25f, 0.25f,
        0.25f,-0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,
        0.25f,-0.25f,-0.25f,
        0.25f, 0.25f,-0.25f,
        0.25f,-0.25f,-0.25f,
        0.25f, 0.25f, 0.25f,
        0.25f,-0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,
        0.25f, 0.25f,-0.25f,
        -0.25f, 0.25f,-0.25f,
        0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f,-0.25f,
        -0.25f, 0.25f, 0.25f,
        0.25f, 0.25f, 0.25f,
        -0.25f, 0.25f, 0.25f,
        0.25f,-0.25f, 0.25f
    };

    color_t COLOR_YELLOW = {
        255, 255, 0,
    };

    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
}

void Bullet::draw(glm::mat4 VP) {
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

void Bullet::tick() {
    this->position += this->velocity;
    this->velocity += this->acc;
}

bool Bullet::detect_collision(Plane plane) {
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