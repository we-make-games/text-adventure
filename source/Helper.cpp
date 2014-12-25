#include "Helper.hpp"

#include <stdexcept>

using namespace std;

namespace adventure {  

SDL_Window* Helper::getWindow()
{
  return SDL_CreateWindow(
    "Text Adventure",        
    SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, 
    1024,                    
    768,                     
    SDL_WINDOW_MAXIMIZED     
  );
}

  void Helper::setupRenderer(SDL_Renderer* renderer)
  {
    SDL_SetRenderDrawColor( renderer, 50, 50, 50, 255 );
  }  
}
