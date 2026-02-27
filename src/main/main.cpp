#include "framework/application.h"
#include "framework/utils.h"

int main(int argc, char **argv)
{
	// Launch the app (app is a global variable)
	Application* app = new Application( "Computer Graphics 2025-26", 1280, 720);
    app->Init();
    
    //Set bg color
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    while(1){
        //read keystate
        app->keystate = SDL_GetKeyboardState(NULL);
        
        //clear window and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //render frame
        app->Render();
        
        //swap between fb and bb
        SDL_GL_SwapWindow(app->window);
    }
	

	std::cout << "Starting loop..." << std::endl;
	launchLoop(app);
    
	SDL_Window* window = app->window;
    
	delete app;
    
	if (window) {
		SDL_DestroyWindow(window);
	}
    
	return 0;
}
