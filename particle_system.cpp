
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "main/includes.h"
#include "framework.h"
#include "particle_system.h"
#include "image.h


float RandRange(float min, float max)
{
    return min + (float(rand()) / float(RAND_MAX)) * (max - min);
}

class Image;

class ParticleSystem {
    static const int MAX_PARTICLES = 50;
    struct Particle {
            Vector2 position;
            Vector2 velocity; // Normalized speed and direction of the particle
            Color color;
            float acceleration;
            float ttl; // Time left until the particle expires
            bool inactive; // Particle is not used/expired, so it can be recreated
    };
    
    Particle particles[MAX_PARTICLES];

public:
    void Init(){
        for (int i = 0; i < MAX_PARTICLES; ++i){
            particles[i].position = Vector2(RandRange(0.0, 800.0), RandRange(0.0, 600.0));
            particles[i].velocity = Vector2(RandRange(-0.2, 0.2), RandRange(-1.0, -0.5));
            particles[i].velocity.normalize();
            particles[i].acceleration = RandRange(20.0, 60.00);
            particles[i].ttl = RandRange(5.0, 10.0);
            particles[i].inactive = false;
            particles[i].color = Color(255, 255, 255);
        }
    };
    
    void Render(Image* framebuffer){
        for (int i = 0; i < MAX_PARTICLES; ++i){
            const Particle& p = particles[i];
            if (p.inactive) continue;
            int x = int (p.position.x);
            int y = int (p.position.y);
            framebuffer->SetPixel(x, y, p.color);
        }
    };
    
    void Update(float dt){
        for (int i = 0; i < MAX_PARTICLES; ++i){
            const Particle& p = particles[i];
            if (p.inactive) continue;
            p.position += p.velocity * p.acceleration * dt;
            
            if (p.position.x < 0.0){
                p.position = Vector2(RandRange(0.0, 800.0), 600.0);
                p.velocity = Vector2(RandRange(-2.0, 2.0), RandRange(-1.0, -0.5));
                p.velocity.normalize();
            }
        }
    };
};
