#pragma once

#include "shader.h"
#include "texture.h"
#include "framework.h"

struct sLight
{
    Vector3 position;
    Vector3 intensity;
};

class Material
{
public:

    Shader* shader;
    Texture* color_texture;
    Texture* normal_texture;
    Vector3 ka;
    Vector3 kd;
    Vector3 ks;
    float shininess;

    Material();
    //void Enable();
    void Disable();
    void Enable(const sUniformData& uniformData);
};
