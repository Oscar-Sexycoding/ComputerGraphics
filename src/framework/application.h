#pragma once

#include "main/includes.h"
#include "framework.h"
#include "image.h"
#include "camera.h"
#include "mesh.h"
#include "material.h"

class Application
{
public:

	// Window
	SDL_Window* window = nullptr;
	int window_width;
	int window_height;
    int rect_border_width;
    
    //Lab 4
    Mesh* quad_mesh = nullptr;
    Shader* current_shader = nullptr;
    Texture* image_texture = nullptr;
    int current_task;
    int current_subtask;
    
    Camera* camera = nullptr;
    Entity* entity = nullptr;
    Shader* raster_shader = nullptr;
    
    sUniformData uniformData;
    Vector3 ambient_light;
    sLight main_light;
    
	float time;

	// Input
	const Uint8* keystate;
	int mouse_state; // Tells which buttons are pressed
	Vector2 mouse_position; // Last mouse position
	Vector2 mouse_delta; // Mouse movement in the last frame
    

	void OnKeyPressed(SDL_KeyboardEvent event);
	void OnMouseButtonDown(SDL_MouseButtonEvent event);
	void OnMouseButtonUp(SDL_MouseButtonEvent event);
	void OnMouseMove(SDL_MouseButtonEvent event);
	void OnWheel(SDL_MouseWheelEvent event);
	void OnFileChanged(const char* filename);

	// CPU Global framebuffer
	//Image framebuffer;

	// Constructor and main methods
	Application(const char* caption, int width, int height);
	~Application();

	void Init( void );
	void Render( void );
	void Update( float dt );

	// Other methods to control the app
	void SetWindowSize(int width, int height) {
		glViewport( 0,0, width, height);
		this->window_width = width;
		this->window_height = height;
		//this->framebuffer.Resize(width, height);
	}

	Vector2 GetWindowSize()
	{
		int w,h;
		SDL_GetWindowSize(window,&w,&h);
		return Vector2(float(w), float(h));
	}
};
