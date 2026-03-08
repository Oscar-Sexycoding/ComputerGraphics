#include "main/includes.h"
#include "framework.h"
#include "entity.h"


Entity::Entity(Mesh* me, Matrix44 mo){
    this->mesh = me;
    this->model = mo;
}

