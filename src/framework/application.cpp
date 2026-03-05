#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"

#include "framework.h"
#include "image.h"

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

	this->framebuffer.Resize(w, h);
}

Application::~Application()
{
}

void Application::Init(void)
{
    quad = new Mesh();
    quad->CreateQuad();

    //Load shader
    shader = Shader::Get("res/shaders/quad.vs", "res/shaders/quad.fs");

    //Load image
    image_texture = Texture::Get("res/images/fruits.png");
    
	std::cout << "Initiating app..." << std::endl;
    
    quad = new Mesh();
    quad->CreateQuad();
    shader = Shader::Get("shaders/quad.vs", "shaders/quad.fs");
}

// Render one frame
void Application::Render(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    shader->Enable();
    shader->SetInt("u_mode", mode);
    shader->SetTexture("u_texture", image_texture);
    quad->Render();
    shader->Disable();
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
        case SDLK_1: mode = 1; break;
        case SDLK_2: mode = 2; break;
        case SDLK_3: mode = 3; break;
        case SDLK_4: mode = 4; break;
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
