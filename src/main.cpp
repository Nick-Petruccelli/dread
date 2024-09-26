#include "../inc/engine.h"
#include "../inc/scene.h"
#include "../inc/window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

bool init();
bool loadMedia();
bool close();

Window gWindow;
SDL_Renderer *gRenderer = NULL;
Scene gScene;

int main(int argc, char *args[]) {
  if (!init()) {
    printf("ERROR::Failed to init\n");
    return -1;
  }
  if (!loadMedia()) {
    printf("ERROR::Failed to load media\n");
    return -1;
  }

  gScene = Scene(gRenderer);
  gScene.addMap("assets/background.png");
  gScene.addPlayer("assets/objData/player.txt");

  SDL_Event e;
  bool quit = false;
  Uint8 alpha = 255;
  while (quit == false) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      gWindow.eventHandler(e);
      gScene.handelEvents(e);
    }
    Engine::updateDeltaTime();
    gScene.updateSceneState();

    gScene.renderScene();
    SDL_RenderPresent(gRenderer);
  }

  return 0;
}

bool init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDl::Failed to init video\n%s\n", SDL_GetError());
    return false;
  }

  if (!gWindow.init()) {
    printf("SDL::Failed to create window\n%s\n", SDL_GetError());
    return false;
  }

  gRenderer = gWindow.createRenderer();
  if (gRenderer == NULL) {
    printf("SDL::Failed to create renderer\n%s\n", SDL_GetError());
    return false;
  }
  SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("ERROR::SDL::Failed to init image loading\n%s\n", SDL_GetError());
    return false;
  }

  return true;
}

bool loadMedia() {
  bool success = true;

  return success;
}

bool close() {
  gWindow.free();
  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;
  IMG_Quit();
  SDL_Quit();

  return true;
}
