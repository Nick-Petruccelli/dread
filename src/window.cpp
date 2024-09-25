#include "../inc/window.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

extern SDL_Renderer *gRenderer;
const int INITIAL_SCREEN_WIDTH = 640;
const int INITIAL_SCREEN_HEIGHT = 480;
SDL_KeyCode FULLSCREEN_KEY = SDLK_ESCAPE;
const int FULLSCREEN_TYPE = SDL_WINDOW_FULLSCREEN;

Window::Window() {
  mWindow = NULL;
  mWidth = INITIAL_SCREEN_WIDTH;
  mHeight = INITIAL_SCREEN_HEIGHT;
  mKeyboardFocus = false;
  mMouseFocus = false;
  mFullscreen = false;
  mMinimized = false;
}

bool Window::init() {
  mWindow = SDL_CreateWindow("DREAD", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, INITIAL_SCREEN_WIDTH,
                             INITIAL_SCREEN_HEIGHT,
                             SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  return mWindow != NULL;
}

void Window::free() {
  SDL_DestroyWindow(mWindow);
  mWindow = NULL;
}

SDL_Renderer *Window::createRenderer() {
  return SDL_CreateRenderer(
      mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void Window::eventHandler(SDL_Event e) {
  if (e.type == SDL_WINDOWEVENT) {
    switch (e.window.event) {
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      mWidth = e.window.data1;
      mHeight = e.window.data2;
      SDL_RenderPresent(gRenderer);
      break;

    case SDL_WINDOWEVENT_EXPOSED:
      SDL_RenderPresent(gRenderer);
      break;

    case SDL_WINDOWEVENT_ENTER:
      mMouseFocus = true;
      break;

    case SDL_WINDOWEVENT_LEAVE:
      mMouseFocus = false;
      break;

    case SDL_WINDOWEVENT_FOCUS_GAINED:
      mKeyboardFocus = true;
      break;

    case SDL_WINDOWEVENT_FOCUS_LOST:
      mKeyboardFocus = false;
      break;

    case SDL_WINDOWEVENT_MINIMIZED:
      mMinimized = true;
      break;

    case SDL_WINDOWEVENT_MAXIMIZED:
      mMinimized = false;
      break;

    case SDL_WINDOWEVENT_RESTORED:
      mMinimized = true;
      break;
    }
  } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == FULLSCREEN_KEY) {
    if (mFullscreen) {
      SDL_SetWindowFullscreen(mWindow, 0);
      mFullscreen = false;
    } else {
      SDL_SetWindowFullscreen(mWindow, FULLSCREEN_TYPE);
      mFullscreen = true;
    }
  }
}

int Window::getWidth() { return mWidth; }

int Window::getHeight() { return mHeight; }

float Window::getScale() { return (float)mWidth / (float)INITIAL_SCREEN_WIDTH; }

bool Window::hasMouseFocus() { return mMouseFocus; }

bool Window::hasKeyboardFocus() { return mKeyboardFocus; }

bool Window::isMinimized() { return mMinimized; }

bool Window::isFullscreen() { return mFullscreen; }
