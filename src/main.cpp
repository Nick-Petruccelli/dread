#include "../inc/engine.h"
#include "../inc/scene.h"
#include "../inc/ui.h"
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
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <sstream>
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

  UI ui;
  ui.setFont("assets/fonts/OpenSans-Regular.ttf");
  ui.addTextElement(0, 0, "FPS: ", {0, 0, 0, 255});
  ui.addTextElement(55, 0, "00", {0, 0, 0, 255});

  gScene = Scene(gRenderer);
  gScene.addMap("assets/background.png");
  gScene.addPlayer("assets/objData/player.txt");

  int framesScinceLast = 0;
  unsigned int timeScinceLast = SDL_GetTicks();
  std::stringstream fpsText;

  SDL_Event e;
  bool quit = false;
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

    if (framesScinceLast >= 200) {
      UI_Element *fpsElm = ui.getElement(1);
      fpsText.str("");
      fpsText << framesScinceLast /
                     ((SDL_GetTicks() - timeScinceLast) / 1000.0);
      fpsElm->texture->loadFromText(ui.getFont(), fpsText.str().c_str(),
                                    {0, 0, 0, 255});
      framesScinceLast = 0;
      timeScinceLast = SDL_GetTicks();
    }

    ui.render();
    SDL_RenderPresent(gRenderer);
    framesScinceLast++;
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

  if (TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
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
