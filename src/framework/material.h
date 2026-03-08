#pragma once

#include "framework.h"
#include "shader.h"
#include "texture.h"

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
    
    bool show_color_texture;
    bool show_specular_texture;
    bool show_normal_texture;
};

class Material
{
public:

    Shader* shader;
    Texture* color_texture; //Includes specular
    Texture* normal_texture;
    Vector3 Ka; // Ambient component
    Vector3 Kd; // Diffuse component
    Vector3 Ks; // Specular component
    float shininess;

    Material();
    void Disable();
    void Enable(const sUniformData& uniformData);
};
