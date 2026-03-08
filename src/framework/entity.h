#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "framework.h"
#include "material.h"

class Entity {
public:
    Mesh* mesh;
    Matrix44 model;
    
    //Lab 4
    //Shader* shader;
    //Texture* texture;
    Material* material;
    //void Render(Camera* camera);
    void Render(sUniformData& uniformData);
    
    Entity(Mesh* me, Matrix44 mo);
};

