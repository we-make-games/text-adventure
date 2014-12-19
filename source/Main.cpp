<SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
 
#include <iostream>
#include <string>

 // Setup
bool InitEverything();
bool InitSDL();
bool CreateWindow();
bool CreateRenderer();
void SetupRenderer();
 
// Setup TTF
bool setupTtf( const std::string &fontName );
SDL_Texture* SurfaceToTexture( SDL_Surface* surf );
void CreateTextTextures();
 
// Update
void Render();
void RunGame();
 
TTF_Font* font;
SDL_Color textColor = { 255, 255, 255, 255 };
SDL_Color backgroundColor = { 0, 0, 0, 255 };
 
SDL_Texture* solidTexture;
SDL_Texture* blendedTexture;
SDL_Texture* shadedTexture;
 
SDL_Rect solidRect;
SDL_Rect blendedRect;
SDL_Rect shadedRect;
 
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
 
  RunGame();
 
  TTF_CloseFont( font );
}
void RunGame()
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
 
  SDL_RenderCopy( renderer, solidTexture, nullptr, &solidRect );
  SDL_RenderCopy( renderer, blendedTexture, nullptr, &blendedRect );
  SDL_RenderCopy( renderer, shadedTexture, nullptr, &shadedRect );
 
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
  SDL_Surface* solid = TTF_RenderText_Solid( font, text.c_str(), textColor );
  solidTexture = SurfaceToTexture( solid );
 
  SDL_QueryTexture( solidTexture, NULL, NULL, &solidRect.w, &solidRect.h );
  solidRect.x = 0;
  solidRect.y = 0;
 
  SDL_Surface* blended = TTF_RenderText_Blended( font, "enter", textColor );
  blendedTexture = SurfaceToTexture( blended );
 
  SDL_QueryTexture( blendedTexture, NULL, NULL, &blendedRect.w, &blendedRect.h );
  blendedRect.x = 0;
  blendedRect.y = solidRect.y + solidRect.h + 20;
 
  SDL_Surface* shaded = TTF_RenderText_Shaded( font, "quit", textColor, backgroundColor );
  shadedTexture = SurfaceToTexture( shaded );
 
  SDL_QueryTexture( shadedTexture , NULL, NULL, &shadedRect.w, &shadedRect.h );
  shadedRect.x = 0;
  shadedRect.y = blendedRect.y + blendedRect.h + 20;
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
 
  if ( !CreateWindow() )
    return false;
 
  if ( !CreateRenderer() )
    return false;
 
  SetupRenderer();
 
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
bool CreateWindow()
{
  window = SDL_CreateWindow( "Server", windowRect.x, windowRect.y, windowRect.w, windowRect.h, 0 );
 
  if ( window == nullptr )
    {
      std::cout << "Failed to create window : " << SDL_GetError();
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
void SetupRenderer()
{
  // Set size of renderer to the same as window
  SDL_RenderSetLogicalSize( renderer, windowRect.w, windowRect.h );
 
  // Set color of renderer to red
  SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
}
