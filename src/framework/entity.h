#include "mesh.h"

#pragma once

class Image;
class FloatImage;
struct sTriangleInfo;

enum class eRenderMode {POINTCLOUD, WIREFRAME, TRIANGLES, TRIANGLES_INTERPOLATED};

struct sTriangleInfo {
    Vector3 p[3];
    Vector2 uv[3];
    Color color[3];
    Image* texture;
};

class Entity {
public:
    
    Mesh* mesh;
    Matrix44 model;
    Image* texture;
    eRenderMode mode;
    
    bool use_texture = true;
    bool use_occlusions = true;
    
    Entity(Mesh* me, Matrix44 mo);
    ~Entity();
    
    void Render(Image* framebuffer, Camera* camera, FloatImage* zBuffer);

    void UpdateT(float seconds_elapsed);
    void UpdateR(float seconds_elapsed);
    void UpdateS(float seconds_elapsed);
    
};

