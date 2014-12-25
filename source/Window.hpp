#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <SDL2/SDL.h>
#include <iostream>

namespace adventure {

class Window {
public:
  Window();
  SDL_Window* getSdlWindow();
private:
  SDL_Window* window;
};

} 

#endif

