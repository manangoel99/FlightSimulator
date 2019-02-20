#include "main.h"
#include "scoreboard.h"

Segments::Segments(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->number = 0;

    GLfloat rb_buffer[] = {
        0.0f, 0.0f, 0.0f,
        -0.1f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,

        -0.1f, 0.0f, 0.0f,
        -0.1f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f, 
    };

    GLfloat b_buffer[] = {
        -0.1f, 0.1f, 0.0f,
        -0.1f, 0.0f, 0.0f,
        -0.6f, 0.0f, 0.0f,

        -0.6f, 0.0f, 0.0f,
        -0.6f, 0.1f, 0.0f,
        -0.1f, 0.1f, 0.0f,
    };

    GLfloat lb_buffer[] = {
        -0.6f, 0.1f, 0.0f,
        -0.5f, 0.1f, 0.0f,
        -0.5f, 0.5f, 0.0f,

        -0.6f, 0.1f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        -0.6f, 0.5f, 0.0f, 
    };

    GLfloat lt_buffer[] = {
        -0.5f, 0.5f, 0.0f,
        -0.6f, 0.5f, 0.0f,
        -0.6f, 1.0f, 0.0f,

        -0.6f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        -0.5f, 1.0f, 0.0f,
    };

    GLfloat t_buffer[] = {
        -0.6f, 1.0f, 0.0f,
        -0.6f, 1.1f, 0.0f,
        -0.1f, 1.1f, 0.0f,

        -0.6f, 1.0f, 0.0f,
        -0.1f, 1.1f, 0.0f,
        -0.1f, 1.0f, 0.0f,
    };

    GLfloat rt_buffer[] = {
        -0.1f, 1.1f, 0.0f,
        0.0f, 1.1f, 0.0f,
        0.0f, 0.6f, 0.0f,

        -0.1f, 0.6f, 0.0f,
        0.0f, 0.6f, 0.0f,
        -0.1f, 1.1f, 0.0f,
    };

    GLfloat m_buffer[] = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, 0.6f, 0.0f,
        0.0f, 0.6f, 0.0f,

        -0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.6f, 0.0f,
    };

    for (int i = 0; i < 18; i++) {
        this->right_bottom_buffer[i] = rb_buffer[i];
        this->bottom_buffer[i] = b_buffer[i];
        this->left_bottom_buffer[i] = lb_buffer[i];
        this->left_top_buffer[i] = lt_buffer[i];
        this->top_buffer[i] = t_buffer[i];
        this->right_top_buffer[i] = rt_buffer[i];
        this->middle_buffer[i] = m_buffer[i];
    }

    this->set_number(0);
}

void Segments::set_number(int n) {

    this->bottom = create3DObject(GL_TRIANGLES, 6, this->bottom_buffer, COLOR_BACKGROUND, GL_FILL);
    this->left_bottom = create3DObject(GL_TRIANGLES, 6, this->left_bottom_buffer, COLOR_BACKGROUND, GL_FILL);
    this->left_top = create3DObject(GL_TRIANGLES, 6, this->left_top_buffer, COLOR_BACKGROUND, GL_FILL);
    this->middle = create3DObject(GL_TRIANGLES, 6, this->middle_buffer, COLOR_BACKGROUND, GL_FILL);
    this->top = create3DObject(GL_TRIANGLES, 6, this->top_buffer, COLOR_BACKGROUND, GL_FILL);
    this->right_bottm = create3DObject(GL_TRIANGLES, 6, this->right_bottom_buffer, COLOR_BACKGROUND, GL_FILL);
    this->right_top = create3DObject(GL_TRIANGLES, 6, this->right_top_buffer, COLOR_BACKGROUND, GL_FILL);

    if (n != 0) {
        if (n != 1 and n != 4 and n != 7) {
            this->bottom = create3DObject(GL_TRIANGLES, 6, this->bottom_buffer, COLOR_BLACK, GL_FILL);
        }

        if (n == 2 or n == 6 or n == 8) {
            this->left_bottom = create3DObject(GL_TRIANGLES, 6, this->left_bottom_buffer, COLOR_BLACK, GL_FILL);
        }

        if (n != 1 and n != 2 and n != 3 and n != 7) {
            this->left_top = create3DObject(GL_TRIANGLES, 6, this->left_top_buffer, COLOR_BLACK, GL_FILL);            
        }

        if (n != 7 and n != 1) {
            this->middle = create3DObject(GL_TRIANGLES, 6, this->middle_buffer, COLOR_BLACK, GL_FILL);
        }

        if (n != 1 and n != 4) {
            this->top = create3DObject(GL_TRIANGLES, 6, this->top_buffer, COLOR_BLACK, GL_FILL);            
        }

        if (n != 2) {
            this->right_bottm = create3DObject(GL_TRIANGLES, 6, this->right_bottom_buffer, COLOR_BLACK, GL_FILL);
        }

        if (n != 5 and n != 6) {
            this->right_top = create3DObject(GL_TRIANGLES, 6, this->right_top_buffer, COLOR_BLACK, GL_FILL);
        }
    }
    else {
        this->bottom = create3DObject(GL_TRIANGLES, 6, this->bottom_buffer, COLOR_BLACK, GL_FILL);
        this->left_bottom = create3DObject(GL_TRIANGLES, 6, this->left_bottom_buffer, COLOR_BLACK, GL_FILL);
        this->left_top = create3DObject(GL_TRIANGLES, 6, this->left_top_buffer, COLOR_BLACK, GL_FILL);
        //this->middle = create3DObject(GL_TRIANGLES, 6, this->middle_buffer, COLOR_BLACK, GL_FILL);
        this->top = create3DObject(GL_TRIANGLES, 6, this->top_buffer, COLOR_BLACK, GL_FILL);
        this->right_bottm = create3DObject(GL_TRIANGLES, 6, this->right_bottom_buffer, COLOR_BLACK, GL_FILL);
        this->right_top = create3DObject(GL_TRIANGLES, 6, this->right_top_buffer, COLOR_BLACK, GL_FILL);
    }
}

void Segments::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    //glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->bottom);
    draw3DObject(this->left_bottom);
    draw3DObject(this->left_top);
    draw3DObject(this->right_bottm);
    draw3DObject(this->right_top);
    draw3DObject(this->top);
    draw3DObject(this->middle);
}