#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HIGHT = 480;

bool init();
bool loadMedia();
bool close();
SDL_Surface *loadSurface(std::string path);

SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL;
SDL_Surface *gCurrentSurface = NULL;

enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

int main(int argc, char *args[]) {
  if (!init()) {
    printf("ERROR::Failed to init\n");
    return -1;
  }
  if (!loadMedia()) {
    printf("ERROR::Failed to load media\n");
    return -1;
  }

  gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
  SDL_Event e;
  bool quit = false;
  while (quit == false) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_UP:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
          break;

        case SDLK_DOWN:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
          break;

        case SDLK_LEFT:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
          break;

        case SDLK_RIGHT:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
          break;

        defualt:
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
          break;
        }
      }
    }
    SDL_BlitSurface(gCurrentSurface, NULL, gSurface, NULL);
    SDL_UpdateWindowSurface(gWindow);
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

  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("ERROR::SDL::Failed to init image loading\n%s\n", SDL_GetError());
    return false;
  }
  gSurface = SDL_GetWindowSurface(gWindow);

  return true;
}

bool loadMedia() {
  bool success = true;

  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] =
      loadSurface("assets/press.png");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    printf("Failed to load default image!\n");
    success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("assets/up.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
    printf("Failed to load up image!\n");
    success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("assets/down.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
    printf("Failed to load down image!\n");
    success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("assets/left.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
    printf("Failed to load left image!\n");
    success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("assets/right.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
    printf("Failed to load right image!\n");
    success = false;
  }

  return success;
}

SDL_Surface *loadSurface(std::string path) {
  SDL_Surface *surf = IMG_Load(path.c_str());
  if (surf == NULL) {
    printf("ERROR::SDL::Failed to load surface\n%s\n", SDL_GetError());
  }
  surf = SDL_ConvertSurface(surf, gSurface->format, 0);
  return surf;
}

bool close() {
  SDL_FreeSurface(gSurface);
  gSurface = NULL;
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_Quit();

  return true;
}
