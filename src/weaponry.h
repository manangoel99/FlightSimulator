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

class Missile {
    public:
        Missile() {}
        Missile (Plane plane);
        void draw_left(glm::mat4 VP);
        void draw_right(glm::mat4 VP);
        void tick();
        glm::vec3 left_position;
        glm::vec3 right_position;
        float rotation;
        float pitch;
        float roll;
        float yaw;
        bool CanonCollision(Canon canon);
        bool ParachuteCollision(Parachute parachute);
        glm::vec3 velocity;
        glm::vec3 acc;
    private:
        VAO *left_object;
        VAO *right_object;
};

#endif // !WEAPONRY_H