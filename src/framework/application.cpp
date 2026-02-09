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
    
    camera = new Camera();

    camera->LookAt(Vector3(0.f, 0.f, 1.5f), Vector3(0.f, -0.5f, 0.f), Vector3(0.f, -1.f, 0.f));
   
    camera->SetPerspective(45.f, (float)window_width / (float)window_height, 0.1f, 50.f);
    
    mesh1 = new Mesh();
    mesh1->LoadOBJ("meshes/lee.obj");
    
    mesh2 = new Mesh();
    mesh2->LoadOBJ("meshes/anna.obj");
    
    mesh3 = new Mesh();
    mesh3->LoadOBJ("meshes/cleo.obj");

    Matrix44 model_matrix;
    model_matrix.MakeTranslationMatrix(0.f, -0.5f, 0.f);
    ent1 = new Entity(mesh1, model_matrix);
    
    model_matrix.MakeTranslationMatrix(1.f, -0.5f, 0.f);
    ent2 = new Entity(mesh2, model_matrix);
    
    model_matrix.MakeTranslationMatrix(-1.f, -0.5f, 0.f);
    ent3 = new Entity(mesh3, model_matrix);
    
	std::cout << "Initiating app..." << std::endl;
}

// Render one frame
void Application::Render(void)
{
    framebuffer.Fill(Color::BLACK);
    
    ent1->Render(&framebuffer, camera, Color::BLUE);
    ent2->Render(&framebuffer, camera, Color::RED);
    ent3->Render(&framebuffer, camera, Color::YELLOW);
    
    framebuffer.Render();
}



// Called after render
void Application::Update(float seconds_elapsed)
{
    time += seconds_elapsed;
    ent1->UpdateT(time);
    ent2->UpdateR(seconds_elapsed);
    ent3->UpdateR(seconds_elapsed);
    ent1->UpdateS(time);
}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
    // KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
    switch(event.keysym.sym) {
        case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
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
	float dy = event.preciseY;

	// ...
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}
