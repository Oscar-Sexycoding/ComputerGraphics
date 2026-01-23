//  partile_system.h
//  ComputerGraphics
#pragma once

#include "main/includes.h"
#include "framework.h"

class Image;

class ParticleSystem
{
    static const int MAX_PARTICLES = 50;

    struct Particle {
        Vector2 position;
        Vector2 velocity;
        Color color;
        float acceleration;
        float ttl;
        bool inactive;
    };

    Particle particles[MAX_PARTICLES];

public:
    void Init(float w, float h);
    void Render(Image* framebuffer);
    void Update(float dt);
};
