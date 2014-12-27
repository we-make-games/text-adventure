#include "Window.hpp"

#include <stdexcept>

using namespace std;

namespace adventure {  

  Window::Window()
  {
      if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
      std::cout <<
      " Failed to initialize SDL : " << SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow(
                              "Text Adventure",        
                              SDL_WINDOWPOS_UNDEFINED, 
                              SDL_WINDOWPOS_UNDEFINED, 
                              1024,                    
                              768,                     
                              SDL_WINDOW_MAXIMIZED     
                              );
  }  
  
  SDL_Window* Window::getSdlWindow()
  {
    return window;
  }
}
