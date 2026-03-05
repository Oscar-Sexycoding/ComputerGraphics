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
    quad_mesh = new Mesh();
    quad_mesh->CreateQuad();

    //Load shader
    current_shader = Shader::Get("res/shaders/quad.vs", "res/shaders/quad.fs");

    //Load image
    image_texture = Texture::Get("res/images/fruits.png");
    
	std::cout << "Initiating app..." << std::endl;
}

// Render one frame
void Application::Render(void)
{
    //Set bg color
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (current_shader) {
        current_shader->Enable();
        
        current_shader->SetFloat("u_time", time);
        current_shader->SetInt("u_task", current_task);
        
        if (image_texture) {
            current_shader->SetTexture("u_texture", image_texture);
        }

        //Draw mesh
        quad_mesh->Render();

        current_shader->Disable();
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
