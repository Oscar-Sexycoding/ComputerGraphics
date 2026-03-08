#include "main/includes.h"
#include "entity.h"
#include "material.h"

Entity::Entity(Mesh* me, Matrix44 mo){
    this->mesh = me;
    this->model = mo;
}
/*
void Entity::Render(Camera* camera){
    //shader->Enable();

    //shader->SetMatrix44("u_model", model);
    //shader->SetMatrix44("u_viewprojection", camera->viewprojection_matrix);
    //shader->SetTexture("u_texture", texture);
    if(!mesh || !material) return;
    material->Enable();
    material->shader->SetMatrix44("u_model", model);
    material->shader->SetMatrix44("u_viewprojection", camera->viewprojection_matrix);
    mesh->Render(GL_TRIANGLES);
    material->Disable();
    
    //mesh->Render();

    //shader->Disable();
}
*/

void Entity::Render(sUniformData& uniformData){
    
    //Update model matrix
    uniformData.model_matrix = this->model;
    material->Enable(uniformData);

    mesh->Render();

    material->Disable();
};


