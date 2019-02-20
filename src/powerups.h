#include "main.h"
#include "plane.h"

#ifndef POWERUPS_H
#define POWERUPS_H

class LifePowerUp {
    public:
        LifePowerUp () {}
        LifePowerUp (float x, float y, float z);
        color_t COLOR;
        glm::vec3 position;
        float rotation;
        bool CheckCollision(Plane plane);
        void draw(glm::mat4 VP);
    private:
        VAO *object;
};

class FuelPowerUp {
    public:
        FuelPowerUp() {}
        FuelPowerUp (float x, float y, float z);
        color_t COLOR;
        glm::vec3 position;
        float rotation;
        bool CheckCollision(Plane plane);
        void draw(glm::mat4 VP);

    private:
        VAO *object;
};

#endif // !POWERUPS_H