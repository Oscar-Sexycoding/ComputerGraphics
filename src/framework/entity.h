#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "framework.h"

class Entity {
public:
    Mesh* mesh;
    Matrix44 model;
    Camera* camera;
    
    //Lab 4
    Shader* shader;
    Texture* texture;
    void Render(Camera* camera);
    
    Entity(Mesh* me, Matrix44 mo);
};

