#include "mesh.h"
#include "camera.h"
#include "framework.h"

class Entity {
public:
    Mesh* mesh;
    Matrix44 model;
    Camera* camera;
    
    Entity(Mesh* me, Matrix44 mo);
    void Render(Camera* camera);

