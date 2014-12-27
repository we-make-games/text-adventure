#include "Helper.hpp"

#include <stdexcept>

using namespace std;

namespace adventure {  

  void Helper::setupRenderer(SDL_Renderer* renderer)
  {
    SDL_SetRenderDrawColor( renderer, 50, 50, 50, 255 );
  }  
}
