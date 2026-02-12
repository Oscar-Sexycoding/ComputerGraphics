#include "main/includes.h"
#include "entity.h"
#include "framework.h"
#include <cmath>
#include "image.h"

Entity::Entity(Mesh* me, Matrix44 mo){
    this->mesh = me;
    this->model = mo;
    this->mode = eRenderMode::WIREFRAME;
}

void Entity::Render(Image* framebuffer, Camera* camera, FloatImage* zBuffer){
    const std::vector<Vector3>& vertices = mesh->GetVertices();
    
    //Lab 3
    const std::vector<Vector2>& uvs = mesh->GetUVs();
    
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
        
        //Lab 3
        Color color0 = Color::RED;
        Color color1 = Color::GREEN;
        Color color2 = Color::BLUE;
        
        
        
        switch(this->mode){
            case eRenderMode::POINTCLOUD:
                framebuffer->SetPixel((int)s0.x, (int)s0.y, color0);
                framebuffer->SetPixel((int)s1.x, (int)s1.y, color0);
                framebuffer->SetPixel((int)s2.x, (int)s2.y, color0);
                break;
            case eRenderMode::WIREFRAME: //Lab 2
                framebuffer->DrawLineDDA((int)s0.x, (int)s0.y, (int)s1.x, (int)s1.y, color2);
                framebuffer->DrawLineDDA((int)s1.x, (int)s1.y, (int)s2.x, (int)s2.y, color2);
                framebuffer->DrawLineDDA((int)s2.x, (int)s2.y, (int)s0.x, (int)s0.y, color2);
                break;
            case eRenderMode::TRIANGLES:
                
                framebuffer->DrawTriangle(s0, s1, s2, color1, true, color1);
                break;
            case eRenderMode::TRIANGLES_INTERPOLATED:
                Vector3 p0(s0.x, s0.y, c0.z);
                Vector3 p1(s1.x, s1.y, c1.z);
                Vector3 p2(s2.x, s2.y, c2.z);
                sTriangleInfo triangle;
                triangle.p[0] = p0; triangle.p[1] = p1; triangle.p[2] = p2;
                triangle.uv[0] = uvs[i]; triangle.uv[1] = uvs[i+1]; triangle.uv[2] = uvs[i+2];
                if(use_occlusions){
                    if(use_texture){
                        triangle.texture = this->texture;
                        framebuffer->DrawTriangleInterpolated(triangle, zBuffer);
                    }
                    else{
                        triangle.color[0] = color0; triangle.color[1] = color1; triangle.color[2] = color2;
                        framebuffer->DrawTriangleInterpolated(p0, p1, p2, color0, color1, color2);
                    }
                }
                else{
                    if(use_texture){
                        triangle.texture = this->texture;
                        framebuffer->DrawTriangleInterpolated(triangle, nullptr);
                    }
                    else{
                        triangle.color[0] = color0; triangle.color[1] = color1; triangle.color[2] = color2;
                        framebuffer->DrawTriangleInterpolated(p0, p1, p2, color0, color1, color2, nullptr);
                    }
                }
                break;
        }
    }
};

void Entity::UpdateT(float seconds_elapsed){
    float x = model.M[3][0];
    float y = model.M[3][1];
    float z = sin(seconds_elapsed/(2*PI));
    model.SetIdentity();
    model.MakeTranslationMatrix(x, y, z);
}

void Entity::UpdateR(float seconds_elapsed){
    Matrix44 rotation_matrix = Matrix44();
    rotation_matrix.MakeRotationMatrix(15 * DEG2RAD * seconds_elapsed, model.TopVector()); //15º per sec
    
    model = rotation_matrix * model;
}

void Entity::UpdateS(float seconds_elapsed){
    float s = 1.f + sin(seconds_elapsed/PI) * 0.5f;

    Vector3 right = model.RightVector().Normalize()*s;
    Vector3 top = model.TopVector().Normalize()*s;
    Vector3 front = model.FrontVector().Normalize()*s;

    model.M[0][0] = right.x; model.M[1][0] = right.y; model.M[2][0] = right.z;
    model.M[0][1] = top.x;   model.M[1][1] = top.y;   model.M[2][1] = top.z;
    model.M[0][2] = front.x; model.M[1][2] = front.y; model.M[2][2] = front.z;
};
