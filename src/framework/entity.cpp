#include "main/includes.h"
#include "entity.h"
#include "framework.h"

Entity::Entity(Mesh* me, Matrix44 mo){
    this->mesh = me;
    this->model = mo;
}

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c){
    const std::vector<Vector3>& vertices = mesh->GetVertices();
    for (unsigned int i = 0; i < vertices.size(); i += 3){
        //Local to World
        Vector3 w0 = model * vertices[i];
        Vector3 w1 = model * vertices[i + 1];
        Vector3 w2 = model * vertices[i + 2];
        
        Vector3 c0 = camera->ProjectVector(w0);
        Vector3 c1 = camera->ProjectVector(w1);
        Vector3 c2 = camera->ProjectVector(w2);
        
        if (c0.x < -1 || c0.x > 1 || c0.y < -1 || c0.y > 1 || c0.z < -1 || c0.z > 1 || c1.x < -1 || c1.x > 1 || c1.y < -1 || c1.y > 1 || c1.z < -1 || c1.z > 1 || c2.x < -1 || c2.x > 1 || c2.y < -1 || c2.y > 1 || c2.z < -1 || c2.z > 1) {
            continue; //Skip triangle
        }
        
        //Clip to screen space
        Vector2 s0, s1, s2;
        s0.x = (c0.x + 1.0) * 0.5 * (float)framebuffer->width;
        s0.y = (1.0 - c0.y) * 0.5 * (float)framebuffer->height;

        s1.x = (c1.x + 1.0) * 0.5 * (float)framebuffer->width;
        s1.y = (1.0 - c1.y) * 0.5 * (float)framebuffer->height;

        s2.x = (c2.x + 1.0) * 0.5 * (float)framebuffer->width;
        s2.y = (1.0 - c2.y) * 0.5 * (float)framebuffer->height;
        
        framebuffer->DrawLineDDA((int)s0.x, (int)s0.y, (int)s1.x, (int)s1.y, c);
        framebuffer->DrawLineDDA((int)s1.x, (int)s1.y, (int)s2.x, (int)s2.y, c);
        framebuffer->DrawLineDDA((int)s2.x, (int)s2.y, (int)s0.x, (int)s0.y, c);
    }
};

void Entity::Update(float seconds_elapsed){
    
    model.SetIdentity();
    Matrix44 rotation_matrix = Matrix44();
    rotation_matrix.MakeRotationMatrix(seconds_elapsed * 0.5f, Vector3(0, 1, 0));
    
    int scale_time = int(seconds_elapsed) % 5;
    Matrix44 scaling_matrix = Matrix44();
    if(scale_time % 2 == 0){ //Even number
        float scale = 1 + (seconds_elapsed - scale_time*5)/5;
        scaling_matrix.MakeScaleMatrix(scale, scale, scale);
    }
    else{
        float scale = 6 - (seconds_elapsed - scale_time*5)/5;
        Matrix44 matrix = Matrix44();
        scaling_matrix.MakeScaleMatrix(scale, scale, scale);
    }
    
    Matrix44 translation_matrix = Matrix44();
    translation_matrix.SetIdentity();
    translation_matrix.M[3][0] = model.M[3][0];
    translation_matrix.M[3][1] = model.M[3][1];
    translation_matrix.M[3][2] = model.M[3][2];
    
    model = translation_matrix * scaling_matrix * rotation_matrix;
    
    
    
}





