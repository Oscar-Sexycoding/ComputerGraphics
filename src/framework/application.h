/*  
	+ This class encapsulates the application, is in charge of creating the data, getting the user input, process the update and render.
*/

#pragma once

#include "main/includes.h"
#include "framework.h"
#include "image.h"
#include "entity.h"

enum eMode {SINGLE_MODE, ANIMATION_MODE};
enum eProperty { NEAR_P, FAR_P, FOV_P };

class Application
{
public:

	// Window
	SDL_Window* window = nullptr;
	int window_width;
	int window_height;
    int rect_border_width;
    
    //Lab 1
    Image canvas;   //Drawing surface
    
    //Lab 2
    
    Camera* camera;
    Entity* ent1;
    Entity* ent2;
    Entity* ent3;
    Mesh* mesh1;
    Mesh* mesh2;
    Mesh* mesh3;
    
    float fov;
    float near;
    float far;
    Vector3 center;
    Vector3 eye;
    Vector3 up;
    
    eMode current_mode;
    eProperty selected_prop;
    
	float time;

	// Input
	const Uint8* keystate;
	int mouse_state; // Tells which buttons are pressed
	Vector2 mouse_position; // Last mouse position
	Vector2 mouse_delta; // Mouse movement in the last frame
    Vector2 last_mouse_position;
    bool left_button = false;
    bool right_button = false;
    float orbit_distance;

	void OnKeyPressed(SDL_KeyboardEvent event);
	void OnMouseButtonDown(SDL_MouseButtonEvent event);
	void OnMouseButtonUp(SDL_MouseButtonEvent event);
	void OnMouseMove(SDL_MouseButtonEvent event);
	void OnWheel(SDL_MouseWheelEvent event);
	void OnFileChanged(const char* filename);

	// CPU Global framebuffer
	Image framebuffer;

	// Constructor and main methods
	Application(const char* caption, int width, int height);
	~Application();

	void Init( void );
	void Render( void );
	void Update( float dt );

	// Other methods to control the app
	void SetWindowSize(int width, int height) {
		glViewport( 0,0, width, height );
		this->window_width = width;
		this->window_height = height;
		this->framebuffer.Resize(width, height);
        camera->UpdateViewProjectionMatrix();
	}

	Vector2 GetWindowSize()
	{
		int w,h;
		SDL_GetWindowSize(window,&w,&h);
		return Vector2(float(w), float(h));
	}
};
