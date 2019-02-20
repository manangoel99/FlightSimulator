#include "main.h"
#include "plane.h"
#define ll long long

using namespace std;
#ifndef CHECKPOINT_H
#define CHECKPOINT_H

class CheckPoint {
    public:
        CheckPoint() {}
        CheckPoint(float x, float y, float z);
        glm::vec3 position;
        float rotation;
        color_t COLOR;
        void draw(glm::mat4 VP);
        bool DetectPassing(Plane plane);
    private:
        VAO *object;
};

#endif // !CHECKPOINT_H