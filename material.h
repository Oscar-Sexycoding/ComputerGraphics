#pragma once

#include "framework.h"
#include "texture.h"
#include "shader.h"

struct sLight
{
    Vector3 position;
    Vector3 intensity;
};

struct sUniformData {
    Matrix44 model_matrix;
    Matrix44 viewprojection_matrix;
    Vector3 ambient_light;
    Vector3 camera_position;
    sLight light;
};

class Material
{
public:

    Shader* shader;
    Texture* color_texture;
    Texture* specular_texture;
    Texture* normal_texture;
    Vector3 Ka; // Ambient component
    Vector3 Kd; // Diffuse component
    Vector3 Ks; // Specular component
    float shininess;

    Material();
    void Disable();
    void Enable(const sUniformData& uniformData);
};
