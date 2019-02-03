#include "main.h"

#ifndef PLANE_H
#define PLANE_H

class Plane {
    public:
        Plane() {}
        Plane(float x, float y, float z, color_t color);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void set_position(float x, float y);
        void tick();
        glm::vec3 speed;
        float roll;
        float pitch;
        float yaw;
    private:
        VAO *object;
        VAO *finobj;
        VAO *wingobj;
};

#endif // !PLANE_H