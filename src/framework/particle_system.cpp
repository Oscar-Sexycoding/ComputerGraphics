#include <cstdlib>
#include "main/includes.h"
#include "framework.h"
#include "particle_system.h"
#include "image.h"


float RandRange(float min, float max)
{
    return min + (float(rand()) / float(RAND_MAX)) * (max - min);
}

void ParticleSystem::Init(float w, float h){
    for (int i = 0; i < MAX_PARTICLES; ++i){
        particles[i].position = Vector2(RandRange(0.0, w), RandRange(0.0, h));
        particles[i].velocity = Vector2(RandRange(-0.2, 0.2), RandRange(-1.5, -0.5));
        particles[i].velocity.normalize();
        particles[i].acceleration = RandRange(30.0, 90.00);
        particles[i].ttl = RandRange(5.0, 10.0);
        particles[i].inactive = false;
        particles[i].color = Color(255, 255, 255);
    }
};
    
void ParticleSystem::Render(Image* framebuffer){
    for (int i = 0; i < MAX_PARTICLES; ++i){
        const Particle& p = particles[i];
        if (p.inactive) continue;
        int x = int (p.position.x);
        int y = int (p.position.y);
        for (int dy = 0; dy < 2; ++dy)
        {
            for (int dx = 0; dx < 2; ++dx)
            {
                framebuffer->SetPixel(x + dx, y + dy, p.color);
            }
        }
    }
};
    
void ParticleSystem::Update(float dt){
    for (int i = 0; i < MAX_PARTICLES; ++i){
        Particle& p = particles[i];
        if (p.inactive) continue;
        p.position += p.velocity * p.acceleration * dt;
        if (p.position.y < 0.0){
            p.position = Vector2(RandRange(0.0, 800.0), 600.0);
        }
    }
};
