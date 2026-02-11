#include "mesh.h"
#include "image.h"

#pragma once

class Entity {
public:
    
    Mesh* mesh;
    Matrix44 model;
    
    Entity(Mesh* me, Matrix44 mo);
    ~Entity();
    
    void Render(Image* framebuffer, Camera* camera, FloatImage* zBuffer);

    void UpdateT(float seconds_elapsed);
    void UpdateR(float seconds_elapsed);
    void UpdateS(float seconds_elapsed);
    
};

