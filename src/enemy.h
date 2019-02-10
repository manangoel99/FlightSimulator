#include "main.h"

#ifndef ENEMIES_H
#define ENEMIES_H

class SmokeRing {
    public:
        SmokeRing() {}
        SmokeRing (float x, float y, float z);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        float radius;
        color_t color;
    private:
        VAO *object;
};

#endif // !ENEMIES_H