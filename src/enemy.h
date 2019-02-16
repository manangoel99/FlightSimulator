#include "main.h"
#include "plane.h"

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
        bool DetectPassing(Plane plane);
    private:
        VAO *object;
};

class Volcano {
    public:
        Volcano() {}
        Volcano(float x, float y, float z);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        float UpperRadius;
        float height;
        float LowerRadius;
        bool DetectPassing(Plane plane);
    private:
        VAO *TopDisc;
        VAO *object;
};

class Canon {
    public:
        Canon() {}
        Canon(float x, float y, float z);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP, glm::vec3 planevec);
        void drawdisc(glm::mat4 VP);
    private:
        VAO *object;
        VAO *disc;
};

class CanonBall {
    public:
        CanonBall() {}
        CanonBall(float x, float y, float z, glm::vec3 planevec);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        bool detect_collision(Plane plane);
        void tick();
        glm::vec3 velocity;
        glm::vec3 acc;
    private:
        VAO *object;
};

#endif // !ENEMIES_H