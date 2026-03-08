#include "main/includes.h"
#include "framework.h"
#include "mesh.h"
#include "camera.h"
#include "entity.h"


Entity::Entity(Mesh* me, Matrix44 mo){
    this->mesh = me;
    this->model = mo;
}

void Entity::Render(Camera* camera){
    
}


