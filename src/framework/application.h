/*  
	+ This class encapsulates the application, is in charge of creating the data, getting the user input, process the update and render.
*/

#pragma once

#include "main/includes.h"
#include "framework.h"
#include "image.h"

//Tools
enum eTool {PENCIL, ERASER, LINE, RECT, TRIANGLE};

//Buttons
enum eButtonType {BTN_PENCIL, BTN_ERASER, BTN_LINE, BTN_RECT, BTN_TRIANGLE, BTN_CLEAR, BTN_LOAD, BTN_SAVE, BTN_BLACK, BTN_WHITE, BTN_PINK, BTN_BLUE, BTN_CYAN, BTN_GREEN, BTN_YELLOW, BTN_RED};

//Modes
enum eAppMode {MODE_PAINT, MODE_ANIMATION};

//Lab 1
class Button {
public:
    Image* icon;
    Vector2 position;
    int type;

    Button(Image* icon, Vector2 pos, int type){
        this->icon = icon;
        this->position = pos;
        this->type = type;
    }

    //Checks if mouse inside button aera
    bool IsMouseInside(Vector2 mousePosition){
        if (mousePosition.x >= position.x && mousePosition.x <= position.x + icon->width && mousePosition.y >= position.y && mousePosition.y <= position.y + icon->height){
            return true;
        }
        return false;
    }

    //Draw button
    void Render(Image& framebuffer){
        framebuffer.DrawImage(*icon, position.x, position.y);
    }
};

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
    
    eTool active_tool;      //Current tool
    Color active_color;      //Current color
    Vector2 mouse_start;       //Starting drag point
    bool is_drawing;     //User state
    
    Color active_fill_color;   //Filling color
    bool target_fill;     //Filling mode or not
    
    Image icon_pencil, icon_line, icon_rectangle, icon_triangle, icon_eraser, icon_clear, icon_save, icon_load;
    Image icon_black, icon_white, icon_pink, icon_blue, icon_cyan, icon_green, icon_yellow, icon_red; //Colors
    std::vector<Button> ui_buttons; //Button list
    int toolbar_height = 50;
    
    eAppMode current_mode;  //Paint or animation
    bool is_filled;

	float time;

	// Input
	const Uint8* keystate;
	int mouse_state; // Tells which buttons are pressed
	Vector2 mouse_position; // Last mouse position
	Vector2 mouse_delta; // Mouse movement in the last frame
    Vector2 last_mouse_position;

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
	}

	Vector2 GetWindowSize()
	{
		int w,h;
		SDL_GetWindowSize(window,&w,&h);
		return Vector2(float(w), float(h));
	}
};
