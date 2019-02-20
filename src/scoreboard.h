#include "main.h"
#define ll long long

using namespace std;

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class Segments {
    public:
        Segments() {}
        Segments (float x, float y, float z);
        int number;
        void draw(glm::mat4 VP);
        glm::vec3 position;
        void set_number(int n);

        GLfloat top_buffer[18];
        GLfloat left_top_buffer[18];
        GLfloat right_top_buffer[18];
        GLfloat middle_buffer[18];
        GLfloat left_bottom_buffer[18];
        GLfloat bottom_buffer[18];
        GLfloat right_bottom_buffer[18];

      private:
        VAO *top;
        VAO *left_top;
        VAO *right_top;
        VAO *middle;
        VAO *left_bottom;
        VAO *right_bottm;
        VAO *bottom;

};

#endif // !SCOREBOARD_H