#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
 
#include <iostream>
#include <string>
#include <queue>
#include "Helper.hpp"
#include "Entity.hpp"
#include "Text.hpp"
#include "Window.hpp"

std::queue<std::string> history;

using namespace adventure;

// Setup
bool InitEverything();
bool InitSDL();
 
// Setup TTF
bool setupTtf( const std::string &fontName );
SDL_Texture* SurfaceToTexture( SDL_Surface* surf );
void createTextTextures();
void handleEvents();
 
// Update
void render();
void runGame();
 
TTF_Font* font;
SDL_Color textColor = { 255, 255, 255, 255 };
SDL_Color backgroundColor = { 0, 0, 0, 255 };
 
SDL_Texture* blendedTexture;
SDL_Texture* blendedTexture2;
 
SDL_Rect blendedRect;
SDL_Rect blendedRect2;
 
SDL_Rect windowRect = { 900, 300, 400, 400 };
SDL_Window* sdl_window;
SDL_Renderer* renderer;
std::string text;
SDL_Event event;
bool done = false;
std::string quitcommand("quit");
Window window;

int main( int argc, char* args[] )
{
  if ( !InitEverything() )
    return -1;
 
  runGame();
 
  TTF_CloseFont( font );
}
void runGame()
{

  while (!done)
    {
      handleEvents();
      createTextTextures();
      render();
    }
  exit(0);
}

void handleEvents(){
  if (SDL_PollEvent(&event))
    {
      switch (event.type)
        {
        case SDL_KEYDOWN:
          if(event.key.keysym.sym == SDLK_BACKSPACE && (text.length() > 0)){
            text.pop_back();
          } else if(event.key.keysym.sym == SDLK_RETURN && (text.length() > 0)){
            text = "";
          }
          break;
          
        case SDL_TEXTINPUT:
          text += event.text.text;
          
          if (text.find(quitcommand) != std::string::npos) {
            done = true;
          }
          break;
        case SDL_TEXTEDITING:
          // char composition[] = event.edit.text;
          int cursor = event.edit.start;
          int selection_len = event.edit.length;
              break;
        }
    }
}

void render()
{
  //  SceneRenderer->render(scene);
  SDL_RenderClear( renderer );
 
  SDL_RenderCopy( renderer, blendedTexture, nullptr, &blendedRect );
  SDL_RenderCopy( renderer, blendedTexture2, nullptr, &blendedRect2 );
 
  SDL_RenderPresent( renderer);
}

bool setupTtf( const std::string &fontName)
{
  if ( TTF_Init() == -1 )
    {
      std::cout << " Failed to initialize TTF : " << TTF_GetError() << std::endl;
      return false;
    }
 
  // Load our fonts, with a huge size
  font = TTF_OpenFont( fontName.c_str(), 90 );
  // Error check
  if ( font == nullptr )
    {
      std::cout << " Failed to load font : " << TTF_GetError() << std::endl;
      return false;
    }
 
  return true;
}

void createTextTextures()
{
  SDL_Surface* blended = TTF_RenderText_Blended( font, text.c_str(), textColor );
  SDL_Surface* blended2 = TTF_RenderText_Blended( font, "enter", textColor );
  blendedTexture = SurfaceToTexture( blended );
  blendedTexture2 = SurfaceToTexture( blended2 );

  blendedRect.x = 400;
  blendedRect.y = 400;

  SDL_QueryTexture( blendedTexture, NULL, NULL, &blendedRect.w, &blendedRect.h );

  blendedRect2.x = 200;
  blendedRect2.y = 200;
  
  SDL_QueryTexture( blendedTexture2, NULL, NULL, &blendedRect2.w, &blendedRect2.h );

}

SDL_Texture* SurfaceToTexture( SDL_Surface* surf )
{
  SDL_Texture* text;
 
  text = SDL_CreateTextureFromSurface( renderer, surf );
 
  SDL_FreeSurface( surf );
 
  return text;
}
bool InitEverything()
{
  if ( !InitSDL() )
    return false;
  //  sdl_window = window->getSdlWindow();
  //  sdl_window = window.getSdlWindow();
  sdl_window = Helper::getWindow();
  if ( sdl_window == nullptr )
    {
      std::cout << "Failed to create window : " << SDL_GetError();
      return false;
    }

  renderer = SDL_CreateRenderer( sdl_window, -1, SDL_RENDERER_ACCELERATED );
 
  if ( renderer == nullptr )
    {
      std::cout << "Failed to create renderer : " << SDL_GetError();
      return false;
    }
  
  Helper::setupRenderer(renderer);
 
  if ( !setupTtf( "./data/fonts/FreeSans.ttf" ) )
    return false;
 
  createTextTextures();
  SDL_StartTextInput();

  return true;
}
bool InitSDL()
{
  if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
      std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
      return false;
    }
 
  return true;
}
