#ifndef HELPER_HPP
#define HELPER_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

namespace adventure {

class Helper {
public:
  static SDL_Window* getWindow();
  static bool setupTtf( const std::string &fontName);
  static void setupRenderer(SDL_Renderer* renderer);
};

} 

#endif

