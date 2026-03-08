#include "main/includes.h"
#include "entity.h"

Entity::Entity(Mesh* me, Matrix44 mo){
    this->mesh = me;
    this->model = mo;
}

void Entity::Render(Camera* camera){
    shader->Enable();

    shader->SetMatrix44("u_model", model);
    shader->SetMatrix44("u_viewprojection", camera->viewprojection_matrix);
    shader->SetTexture("u_texture", texture);

    mesh->Render();

    shader->Disable();
}


