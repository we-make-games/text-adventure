#ifndef HELPER_HPP
#define HELPER_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

namespace adventure {

class Helper {
public:
  static void setupRenderer(SDL_Renderer* renderer);
};

} 

#endif

