#include "mesh.h"
#include "image.h"

#pragma once

class Entity {
public:
    
    Mesh* mesh;
    Matrix44 model;
    
    Entity(Mesh* me, Matrix44 mo);
    ~Entity();
    
    void Render(Image* framebuffer, Camera* camera, const Color& c);

    void Update(float seconds_elapsed);

};

