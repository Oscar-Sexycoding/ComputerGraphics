#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "framework.h"
#include "image.h"
#include "entity.h"

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);
    
    //set bg color
    glClearColor(0.0, 0.0, 0.0, 1.0);

	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->mouse_state = 0;
	this->time = 0.f;
	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(nullptr);

	//this->framebuffer.Resize(w, h);
}

Application::~Application()
{
}

void Application::Init(void)
{
    current_task = 1;
    current_subtask = 1;
    
    //Task 1, 2, 3
    quad_mesh = new Mesh();
    quad_mesh->CreateQuad();

    //Load shader
    current_shader = Shader::Get("shaders/quad.vs","shaders/quad.fs");
    
    //Load texture
    image_texture = Texture::Get("images/fruits.png");
    
    //Task 4
    camera = new Camera();
    camera->LookAt(Vector3(0.f, 0.f, 1.5f), Vector3(0.f, -0.25f, 0.f), Vector3(0.f, 1.f, 0.f));
    camera->SetPerspective(45.f, window_width/(float)window_height, 0.1f, 10.0f);

    //Lab 5
    this->ambient_light = Vector3(0.2f, 0.2f, 0.2f);
    this->main_light.position = Vector3(10.f, 10.f, 10.f);
    this->main_light.intensity = Vector3(1.f, 1.f, 1.f);

    Material* head_material = new Material();
    head_material->shader = Shader::Get("shaders/raster.vs", "shaders/raster.fs");
    head_material->color_texture = Texture::Get("textures/lee_color_specular.tga");
    
    Mesh* head_mesh = new Mesh();
    head_mesh->LoadOBJ("meshes/lee.obj");
    
    Matrix44 model_matrix;
    model_matrix.MakeTranslationMatrix(0.f, -0.5f, 0.f);
    
    entity = new Entity(head_mesh, model_matrix);
    entity->material = head_material;
    
	std::cout << "Initiating app..." << std::endl;
}

// Render one frame
void Application::Render(void)
{
    //Set bg color
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (current_task < 4){
        if (current_shader) {
            current_shader->Enable();
            
            current_shader->SetFloat("u_time", time);
            current_shader->SetInt("u_task", current_task);
            current_shader->SetInt("u_subtask", current_subtask);
            float aspect = (float)window_width / (float)window_height;
            current_shader->SetFloat("u_aspect", aspect);
            
            if (image_texture) {
                current_shader->SetTexture("u_texture", image_texture);
            }
            current_shader->SetVector2("u_texel_size", Vector2(1.0/window_width, 1.0/window_height));
            
            glEnable(GL_DEPTH_TEST);
            
            //Draw mesh
            quad_mesh->Render();
            
            current_shader->Disable();
        }
    }
    else if (current_task == 4){
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        
        camera->SetAspectRatio((float)window_width / (float)window_height);
        camera->UpdateViewProjectionMatrix();
        
        uniformData.viewprojection_matrix = camera->viewprojection_matrix;
        uniformData.camera_position = camera->eye;
        uniformData.ambient_light = this->ambient_light;
        uniformData.light = this->main_light;
        
        entity->Render(uniformData);
    }
}

// Called after render
void Application::Update(float seconds_elapsed)
{
    
}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
    // KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
    switch(event.keysym.sym) {
        case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
        case SDLK_1: current_task = 1; break;
        case SDLK_2: current_task = 2; break;
        case SDLK_3: current_task = 3; break;
        case SDLK_4: current_task = 4; break;
        case SDLK_a: current_subtask = 1; break;
        case SDLK_b: current_subtask = 2; break;
        case SDLK_c: current_subtask = 3; break;
        case SDLK_d: current_subtask = 4; break;
        case SDLK_e: current_subtask = 5; break;
        case SDLK_f: current_subtask = 6; break;
    }
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{

}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{

}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
    
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}
