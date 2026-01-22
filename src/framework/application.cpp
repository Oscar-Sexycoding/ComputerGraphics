#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"

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
    
    // Initialize the border width
    this->rect_border_width = 2;
}

Application::~Application()
{
}

void Application::Init(void)
{
    //Initialize canva
    canvas.Resize(window_width, window_height);
    canvas.Fill(Color::BLACK);
    
    active_tool = PENCIL;
    active_color = Color::WHITE;
    is_drawing = false;
    
    icon_pencil.LoadPNG("images/pencil.png");
    icon_eraser.LoadPNG("images/eraser.png");
    icon_line.LoadPNG("images/line.png");
    icon_rectangle.LoadPNG("images/rectangle.png");
    icon_triangle.LoadPNG("images/triangle.png");
    icon_clear.LoadPNG("images/clear.png");
    icon_load.LoadPNG("images/load.png");
    icon_save.LoadPNG("images/save.png");
    icon_black.LoadPNG("images/black.png");
    icon_white.LoadPNG("images/white.png");
    icon_pink.LoadPNG("images/pink.png");
    icon_blue.LoadPNG("images/blue.png");
    icon_cyan.LoadPNG("images/cyan.png");
    icon_green.LoadPNG("images/green.png");
    icon_yellow.LoadPNG("images/yellow.png");
    icon_red.LoadPNG("images/red.png");
    
    float x = 20;
    float y = 9;
    float spacing = 50;
    
    //Shapes/tools
    ui_buttons.push_back(Button(&icon_pencil, Vector2(x, y), BTN_PENCIL));
    x += spacing;
    ui_buttons.push_back(Button(&icon_eraser, Vector2(x, y), BTN_ERASER));
    x += spacing;
    ui_buttons.push_back(Button(&icon_line, Vector2(x, y), BTN_LINE));
    x += spacing;
    ui_buttons.push_back(Button(&icon_rectangle, Vector2(x, y), BTN_RECT));
    x += spacing;
    ui_buttons.push_back(Button(&icon_triangle, Vector2(x, y), BTN_TRIANGLE));
    x += spacing;

    //Actions
    ui_buttons.push_back(Button(&icon_clear, Vector2(x, y), BTN_CLEAR));
    x += spacing;
    ui_buttons.push_back(Button(&icon_load, Vector2(x, y), BTN_LOAD));
    x += spacing;
    ui_buttons.push_back(Button(&icon_save, Vector2(x, y), BTN_SAVE));
    x += spacing;
    
    //Colors
    ui_buttons.push_back(Button(&icon_black, Vector2(x, y), BTN_BLACK));
    x += spacing;
    ui_buttons.push_back(Button(&icon_white, Vector2(x, y), BTN_WHITE));
    x += spacing;
    ui_buttons.push_back(Button(&icon_pink, Vector2(x, y), BTN_PINK));
    x += spacing;
    ui_buttons.push_back(Button(&icon_blue, Vector2(x, y), BTN_BLUE));
    x += spacing;
    ui_buttons.push_back(Button(&icon_cyan, Vector2(x, y), BTN_CYAN));
    x += spacing;
    ui_buttons.push_back(Button(&icon_green, Vector2(x, y), BTN_GREEN));
    x += spacing;
    ui_buttons.push_back(Button(&icon_yellow, Vector2(x, y), BTN_YELLOW));
    x += spacing;
    ui_buttons.push_back(Button(&icon_red, Vector2(x, y), BTN_RED));
    
	std::cout << "Initiating app..." << std::endl;
}

// Render one frame
void Application::Render(void)
{
	// ...
    
    //Pre-UI section (testing primitives)
    //framebuffer.Fill(Color::BLACK);
    
    //int x = window_width/2;
    //int y = window_height/2;
    
    //DrawLine test
    //framebuffer.DrawLineDDA(x, y, x + 100 * cos(time), y + 100 * sin(time), Color::RED);
    
    //DrawRectangle test
    //int w = 300;
    //int h = 200;
    //framebuffer.DrawRect(x, y, w, h, Color::BLUE, rect_border_width, true, Color::WHITE);
    
    //DrawTriangle test
    //Vector2 p0(500, 240);
    //Vector2 p1(500, 480);
    //Vector2 p2(x + 100 * cos(time), y + 100 * sin(time));
    //framebuffer.DrawTriangle(p0, p1, p2, Color::WHITE, true, Color::PURPLE);
    
    framebuffer = canvas;
    
    //Preview drawings
    if (is_drawing){
        if (active_tool == LINE){
            framebuffer.DrawLineDDA(mouse_start.x, mouse_start.y, mouse_position.x, mouse_position.y, active_color);
        }
        else if (active_tool == RECT){
            float x = std::min(mouse_start.x, mouse_position.x);
            float y = std::min(mouse_start.y, mouse_position.y);
            //Calculate absolutes (if not negative changes are not drawn)
            float w = std::abs(mouse_position.x - mouse_start.x);
            float h = std::abs(mouse_position.y - mouse_start.y);
            framebuffer.DrawRect(x, y, w, h, active_color, 1, false, active_color);
        }
        else if (active_tool == TRIANGLE){
            Vector2 p0(mouse_start.x + (mouse_position.x - mouse_start.x)/2, mouse_start.y);
            Vector2 p1(mouse_start.x, mouse_position.y);
            Vector2 p2(mouse_position.x, mouse_position.y);
            framebuffer.DrawTriangle(p0, p1, p2, active_color, false, active_color);
        }
    }
    
    //Toolbar
    framebuffer.DrawRect(-2, 0, window_width + 1, toolbar_height, Color::WHITE, 1, true, Color::GRAY); //-2 and +1 (if not it wasn't filling the whole width)
    
    //Buttons (and highlight tools and color)
    for (int i = 0; i < ui_buttons.size(); ++i){
        Button& btn = ui_buttons[i];
        btn.Render(framebuffer);
        
        bool isSelectedTool = false;
        if (active_tool == PENCIL && btn.type == BTN_PENCIL){
            isSelectedTool = true;
        }
        if (active_tool == ERASER && btn.type == BTN_ERASER){
            isSelectedTool = true;
        }
        if (active_tool == LINE && btn.type == BTN_LINE){
            isSelectedTool = true;
        }
        if (active_tool == RECT && btn.type == BTN_RECT){
            isSelectedTool = true;
        }
        if (active_tool == TRIANGLE && btn.type == BTN_TRIANGLE){
            isSelectedTool = true;
        }
        
        
        if (isSelectedTool){
            framebuffer.DrawRect(ui_buttons[i].position.x - 2, btn.position.y - 2, btn.icon->width + 4, btn.icon->height + 4, Color::RED, 2, false, Color::RED);
        }
        
        bool isSelectedColor = false;
        if (active_tool == ERASER && btn.type == BTN_BLACK){
                isSelectedColor = true;
        }
        else if (active_tool != ERASER){
            if (btn.type == BTN_BLACK && active_color.r == 0 && active_color.g == 0 && active_color.b == 0){
                isSelectedColor = true;
            }
            if (btn.type == BTN_WHITE && active_color.r == 255 && active_color.g == 255 && active_color.b == 255){
                isSelectedColor = true;
            }
            if (btn.type == BTN_PINK && active_color.r == 255 && active_color.g == 192 && active_color.b == 203){
                isSelectedColor = true;
            }
            if (btn.type == BTN_BLUE  && active_color.r == 0 && active_color.g == 0 && active_color.b == 255){
                isSelectedColor = true;
            }
            if (btn.type == BTN_CYAN && active_color.r == 0 && active_color.g == 255 && active_color.b == 255){
                isSelectedColor = true;
            }
            if (btn.type == BTN_GREEN && active_color.r == 0 && active_color.g == 255 && active_color.b == 0){
                isSelectedColor = true;
            }
            if (btn.type == BTN_YELLOW && active_color.r == 255 && active_color.g == 255 && active_color.b == 0){
                isSelectedColor = true;
            }
            if (btn.type == BTN_RED && active_color.r == 255 && active_color.g == 0 && active_color.b == 0){
                isSelectedColor = true;
            }
        }
        if (isSelectedColor){
            framebuffer.DrawRect(btn.position.x - 2, btn.position.y - 2, btn.icon->width + 4, btn.icon->height + 4, Color::RED, 2, false, Color::RED);
        }
    }
    //DrawImage test
    //Image testIcon;
    //testIcon.LoadPNG("ComputerGraphics/res/images/pencil.png");
    //framebuffer.DrawImage(testIcon, 50, 50);
    framebuffer.Render();
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
            
        //Change border width
        case SDLK_PLUS:
        case SDLK_KP_PLUS:
            rect_border_width++;
            break;
            
        case SDLK_MINUS:
        case SDLK_KP_MINUS:
            if (rect_border_width <= 1){ //Border width can't be negative
                break;
            }
            else {
                rect_border_width--;
                break;
            }
    }
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
    Vector2 mousePos(float (event.x), float (framebuffer.height - event.y));
    bool clicked = false;
    
    for (int i = 0; i < ui_buttons.size(); ++i) {
        if (ui_buttons[i].IsMouseInside(mousePos)) {
            clicked = true;
            int type = ui_buttons[i].type;
            switch (type){
                case BTN_PENCIL:
                    active_tool = PENCIL;
                    break;
                case BTN_LINE:
                    active_tool = LINE;
                    break;
                case BTN_RECT:
                    active_tool = RECT;
                    break;
                case BTN_TRIANGLE:
                    active_tool = TRIANGLE;
                    break;
                case BTN_ERASER:
                    active_tool = ERASER;
                    break;
                    
                    
                case BTN_BLACK:
                    active_color = Color::BLACK;
                    break;
                case BTN_WHITE:
                    active_color = Color::WHITE;
                    break;
                case BTN_PINK:
                    active_color = Color::PINK;
                    break;
                case BTN_BLUE:
                    active_color = Color::BLUE;
                    break;
                case BTN_CYAN:
                    active_color = Color::CYAN;
                    break;
                case BTN_GREEN:
                    active_color = Color::GREEN;
                    break;
                case BTN_YELLOW:
                    active_color = Color::YELLOW;
                    break;
                case BTN_RED:
                    active_color = Color::RED;
                    break;
                    
                case BTN_CLEAR:
                    canvas.Fill(Color::BLACK);
                    break;
                case BTN_SAVE:
                    canvas.SaveTGA("drawing.tga");
                    std::cout << "Image saved to build folder" << std::endl;
                    break;
                case BTN_LOAD:
                    canvas.LoadTGA("drawing.tga");
                    break;
            }
            break;
        }
        if (!clicked && event.button == SDL_BUTTON_LEFT) {
            is_drawing = true;
            mouse_start = mousePos;
        }
    }
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
    if (event.button == SDL_BUTTON_LEFT && is_drawing){
        if (active_tool == LINE){
            canvas.DrawLineDDA(mouse_start.x, mouse_start.y, event.x, framebuffer.height - event.y, active_color);
        }
        else if (active_tool == RECT){
            float x = std::min(mouse_start.x, mouse_position.x);
            float y = std::min(mouse_start.y, mouse_position.y);
            //Calculate absolutes (if not negative changes are not drawn)
            float w = std::abs(mouse_position.x - mouse_start.x);
            float h = std::abs(mouse_position.y - mouse_start.y);
            canvas.DrawRect(x, y, w, h, active_color, 1, false, active_color);
        }
        else if (active_tool == TRIANGLE){
            //Start is top, last point is right vertex
            Vector2 p0(mouse_start.x + (event.x - mouse_start.x)/2, mouse_start.y);
            Vector2 p1(mouse_start.x, framebuffer.height - event.y);
            Vector2 p2(event.x, framebuffer.height - event.y);
            canvas.DrawTriangle(p0, p1, p2, active_color, false, active_color);
        }
        is_drawing = false;
    }
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
    Vector2 currentMouse(event.x, framebuffer.height - event.y);
    
    if (is_drawing && active_tool == PENCIL){
        canvas.DrawLineDDA(last_mouse_position.x, last_mouse_position.y, currentMouse.x, currentMouse.y, active_color);
    }
    else if (is_drawing && active_tool == ERASER){ //Eraser = black pencil
        canvas.DrawLineDDA(last_mouse_position.x, last_mouse_position.y, currentMouse.x, currentMouse.y, Color::BLACK);
    }
    this->last_mouse_position = currentMouse;
    this->mouse_position = currentMouse;
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
