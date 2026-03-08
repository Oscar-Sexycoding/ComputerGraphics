#include "material.h"

Material::Material()
{
    shader = nullptr;
    color_texture = nullptr;
    normal_texture = nullptr;

    Ka = Vector3(0.1f, 0.1f, 0.1f);
    Kd = Vector3(0.8f, 0.6f, 0.4f);
    Ks = Vector3(1.0f, 1.0f, 1.0f);
    shininess = 30.0f;
}

void Material::Enable(const sUniformData& uniformData)
{
    if (!shader) return;
    
    shader->Enable();
    
    shader->SetInt("u_show_color_texture", uniformData.show_color_texture);
    shader->SetInt("u_show_specular_texture", uniformData.show_specular_texture);
    shader->SetInt("u_show_normal_texture", uniformData.show_normal_texture);
    if (color_texture) shader->SetTexture("u_color_texture", color_texture);
    if (normal_texture) shader->SetTexture("u_normal_texture", normal_texture);
    
    shader->SetVector3("u_Ka", Ka);
    shader->SetVector3("u_Kd", Kd);
    shader->SetVector3("u_Ks", Ks);
    shader->SetFloat("u_shininess", shininess);

    shader->SetMatrix44("u_model", uniformData.model_matrix);
    shader->SetMatrix44("u_viewprojection", uniformData.viewprojection_matrix);
    shader->SetVector3("u_camera_pos", uniformData.camera_position);
    shader->SetVector3("u_ambient_light", uniformData.ambient_light);
    shader->SetVector3("u_light_pos", uniformData.light.position);
    shader->SetVector3("u_light_intensity", uniformData.light.intensity);
}

void Material::Disable()
{
    if (shader) shader->Disable();
}
