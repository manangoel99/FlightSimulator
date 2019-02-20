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

class Arrow {
    public:
        Arrow() {}
        Arrow(float x, float y, float z);
        glm::vec3 position;
        float pitch;
        float yaw;

        color_t COLOR;

        void draw(glm::mat4 VP, Plane plane, CheckPoint c);
    private:
        VAO *MainObject;
        VAO *TailObject;
};

#endif // !CHECKPOINT_H