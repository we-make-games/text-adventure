#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
 
#include <iostream>
#include <string>
#include <queue>
#include "Helper.hpp"
std::queue<std::string> history;

using namespace adventure;

// Setup
bool InitEverything();
bool InitSDL();
bool CreateRenderer();
void setupRenderer();
 
// Setup TTF
bool setupTtf( const std::string &fontName );
SDL_Texture* SurfaceToTexture( SDL_Surface* surf );
void CreateTextTextures();
 
// Update
void Render();
void runGame();
 
TTF_Font* font;
SDL_Color textColor = { 255, 255, 255, 255 };
SDL_Color backgroundColor = { 0, 0, 0, 255 };
 
SDL_Texture* blendedTexture;
SDL_Texture* blendedTexture2;
 
SDL_Rect blendedRect;
SDL_Rect blendedRect2;
 
SDL_Rect windowRect = { 900, 300, 400, 400 };
SDL_Window* window;
SDL_Renderer* renderer;
std::string text;
SDL_Event event;
bool done = false;
std::string quitcommand("quit");

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
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
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
        //        Redraw();
        CreateTextTextures();
        Render();
    }
    exit(0);
}
void Render()
{
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

void CreateTextTextures()
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
  window = Helper::getWindow();
  if ( window == nullptr )
    {
      std::cout << "Failed to create window : " << SDL_GetError();
      return false;
    }
  
  if ( !CreateRenderer() )
    return false;
 
  setupRenderer();
 
  if ( !setupTtf( "./data/fonts/FreeSans.ttf" ) )
    return false;
 
  CreateTextTextures();
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

bool CreateRenderer()
{
  renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
 
  if ( renderer == nullptr )
    {
      std::cout << "Failed to create renderer : " << SDL_GetError();
      return false;
    }
 
  return true;
}
void setupRenderer()
{
  SDL_SetRenderDrawColor( renderer, 50, 50, 50, 255 );
}
