#include "main.h"
#include "plane.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H

class LifeBar {
    public:
        LifeBar() {}
        LifeBar (float x, float y, float z);
        void CreateLifeObject(Plane plane);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        VAO *LifeObject;

    private:
        VAO *TotalObject;
};

class HeightBar {
    public:
        HeightBar() {}
        HeightBar (float x, float y, float z);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void UpdateBar(Plane plane);
    private:
        VAO *TotalObject;
        VAO *HeightObject;
};

#endif // !DASHBOARD_H