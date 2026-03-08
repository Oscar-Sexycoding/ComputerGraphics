#include "main/includes.h"
#include "material.h"

Material::Material()
{
    shader = NULL;
    color_texture = NULL;
    normal_texture = NULL;

    ka = Vector3(0.1,0.1,0.1);
    kd = Vector3(1.0,1.0,1.0);
    ks = Vector3(1.0,1.0,1.0);

    shininess = 32.0f;
}
/*
void Material::Enable()
{
    if(shader)
        shader->Enable();

    if(color_texture)
        color_texture->Bind();

    if(normal_texture)
        normal_texture->Bind();
}
*/
void Material::Enable(const sUniformData& uniformData);

void Material::Disable()
{
    if(color_texture)
        color_texture->Unbind();

    if(normal_texture)
        normal_texture->Unbind();

    if(shader)
        shader->Disable();
}
