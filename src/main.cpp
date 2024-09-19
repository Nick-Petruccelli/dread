#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HIGHT = 480;

bool init();
bool loadMedia();
bool close();

SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL;
SDL_Surface *gHelloWorld = NULL;

int main(int argc, char *args[]) {
  if (!init()) {
    printf("ERROR::Failed to init\n");
    return -1;
  }
  if (!loadMedia()) {
    printf("ERROR::Failed to load media\n");
    return -1;
  }

  SDL_BlitSurface(gHelloWorld, NULL, gSurface, NULL);
  SDL_UpdateWindowSurface(gWindow);

  SDL_Event e;
  bool quit = false;
  while (quit == false) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = true;
    }
  }

  return 0;
}

bool init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDl::Failed to init video\n%s\n", SDL_GetError());
    return false;
  }

  gWindow = SDL_CreateWindow("DREAD", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                             SCREEN_HIGHT, SDL_WINDOW_SHOWN);
  if (gWindow == NULL) {
    printf("SDL::Failed to create window\n%s\n", SDL_GetError());
    return false;
  }
  gSurface = SDL_GetWindowSurface(gWindow);

  return true;
}

bool loadMedia() {
  gHelloWorld = SDL_LoadBMP("assets/test.bmp");
  if (gHelloWorld == NULL) {
    printf("ERROR::SDL::Failed to load bit map\n%s\n", SDL_GetError());
    return false;
  }
  return true;
}

bool close() {
  SDL_FreeSurface(gSurface);
  gSurface = NULL;
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_Quit();

  return true;
}
