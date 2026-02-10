#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "entity.h"

#include "framework.h"
#include "image.h"

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->mouse_state = 0;
	this->time = 0.f;
	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(nullptr);

	this->framebuffer.Resize(w, h);
}

Application::~Application()
{
    
}

void Application::Init(void)
{
    //Initialize canva
    canvas.Resize(window_width, window_height);
    canvas.Fill(Color::BLACK);
    
    current_mode = SINGLE_MODE;
    selected_prop = FOV_P;
    fov = 45.f;
    near = 0.1f;
    far = 10.f;
    center = Vector3(0.f, -0.5f, 0.f);
    eye = Vector3(0.f, 0.f, 1.5f);
    up = Vector3(0.f, -1.f, 0.f);
    
    camera = new Camera();
    
    mesh1 = new Mesh();
    mesh1->LoadOBJ("meshes/lee.obj");
    
    Matrix44 model_matrix;
    model_matrix.MakeTranslationMatrix(0.f, -0.5f, 0.f);
    ent1 = new Entity(mesh1, model_matrix);
    
    mesh2 = new Mesh();
    mesh2->LoadOBJ("meshes/anna.obj");
    
    model_matrix.MakeTranslationMatrix(1.f, -0.5f, 0.f);
    ent2 = new Entity(mesh2, model_matrix);
        
    mesh3 = new Mesh();
    mesh3->LoadOBJ("meshes/cleo.obj");
        
    model_matrix.MakeTranslationMatrix(-1.f, -0.5f, 0.f);
    ent3 = new Entity(mesh3, model_matrix);
    
    orbit_distance = eye.Distance(center);
    
	std::cout << "Initiating app..." << std::endl;
}

// Render one frame
void Application::Render(void)
{
    camera->LookAt(eye, center, up);
    camera->SetPerspective(fov, (float)window_width / (float)window_height, near, far);
    
    framebuffer.Fill(Color::BLACK);
    
    if (current_mode == SINGLE_MODE) {
        ent1->model.SetIdentity();
        ent1->model.MakeTranslationMatrix(0.f, -0.5f, 0.f);
        
        ent1->Render(&framebuffer, camera, Color::YELLOW);
    }
    else if (current_mode == ANIMATION_MODE) {
        ent1->Render(&framebuffer, camera, Color::BLUE);
        ent2->Render(&framebuffer, camera, Color::RED);
        ent3->Render(&framebuffer, camera, Color::YELLOW);
    }
    
    framebuffer.Render();
}



// Called after render
void Application::Update(float seconds_elapsed)
{
    if(current_mode == ANIMATION_MODE){
        time += seconds_elapsed;
        ent1->UpdateT(time);
        ent1->UpdateS(time);
        
        ent2->UpdateR(seconds_elapsed);
        ent3->UpdateR(seconds_elapsed);
    }
}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
    // KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
    switch(event.keysym.sym) {
        case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
        case SDLK_1:
            current_mode = SINGLE_MODE;
            break;
            
        case SDLK_2:
            current_mode = ANIMATION_MODE;
            break;
            
        case SDLK_n:
            selected_prop = NEAR_P;
            break;
            
        case SDLK_f:
            selected_prop = FAR_P;
            break;
            
        case SDLK_v:
            selected_prop = FOV_P;
            break;
            
        case SDLK_PLUS:
            if (selected_prop == NEAR_P) near += 0.1f;
            if (selected_prop == FAR_P)  far += 1.0f;
            if (selected_prop == FOV_P)  fov += 1.0f;
            break;
            
        case SDLK_MINUS:
            if (selected_prop == NEAR_P) near -= 0.1f;
            if (selected_prop == FAR_P)  far -= 1.0f;
            if (selected_prop == FOV_P)  fov -= 1.0f;
            
            if (fov < 1.0f) fov = 1.0f;
            if (near < 0.01f) near = 0.01f;
            if (far < near + 0.1f) far = near + 0.1f;
            if (fov > 170.0f) fov = 170.0f;
            break;
    }
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
    last_mouse_position = Vector2(event.x, event.y);
    if(event.button == SDL_BUTTON_LEFT)
        left_button = true;
    else if (event.button == SDL_BUTTON_RIGHT)
        right_button = true;
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
    if(event.button == SDL_BUTTON_LEFT)
        left_button = false;
    else if (event.button == SDL_BUTTON_RIGHT)
        right_button = false;
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
    mouse_position = Vector2(event.x, event.y);
    mouse_delta = mouse_position - last_mouse_position;
    last_mouse_position = mouse_position;
    if (left_button){
        float yaw = mouse_delta.x * 0.005f;
        float pitch = mouse_delta.y * 0.005f;
        Vector3 view = (eye - center).Normalize();
        
        Matrix44 rotY;
        rotY.MakeRotationMatrix(-yaw, up);
        Vector3 right_axis = view.Cross(up).Normalize();
        Matrix44 rotX;
        rotX.MakeRotationMatrix(-pitch, right_axis);
        
        view = rotY * view;
        view = rotX * view;
        view = view.Normalize() * orbit_distance;
        eye = center + view;
    }
    if (right_button){
        float speed = 0.005f;
        Vector3 view = (center - eye).Normalize();
        Vector3 right_axis = view.Cross(up).Normalize();
        Vector3 camera_up = right_axis.Cross(view).Normalize();

        Vector3 offset = (right_axis * -mouse_delta.x + camera_up * -mouse_delta.y) * speed;
        eye = eye + offset;
        center = center + offset;
    }
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;
    float speed_zoom = 1.0f;
    orbit_distance -= dy * speed_zoom;
    
    if (orbit_distance < 0.1f)
        orbit_distance = 0.1f;
    if (orbit_distance > 20.0f)
        orbit_distance = 20.0f;
    
    Vector3 view = (eye - center).Normalize();
    eye = center + view * orbit_distance;
	// ...
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}
