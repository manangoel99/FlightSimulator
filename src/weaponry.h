#include "main.h"
#include "plane.h"
#include "enemy.h"

#ifndef WEAPONRY_H
#define WEAPONRY_H

class Bomb {
    public:
        Bomb() {};
        Bomb(float x, float y, float z, Plane plane);
        void draw(glm::mat4 VP);
        void tick();
        bool detect_collision(Canon canon);
        glm::vec3 position;
        float rotation;
        glm::vec3 velocity;
        glm::vec3 acc;
    private:
        VAO *object;
};

#endif // !WEAPONRY_H