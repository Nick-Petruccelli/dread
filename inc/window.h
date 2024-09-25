#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

class Window {
public:
  Window();
  bool init();
  void free();
  SDL_Renderer *createRenderer();
  void eventHandler(SDL_Event e);
  int getWidth();
  int getHeight();
  float getScale();
  bool hasMouseFocus();
  bool hasKeyboardFocus();
  bool isFullscreen();
  bool isMinimized();

private:
  SDL_Window *mWindow;
  unsigned int mWidth;
  unsigned int mHeight;
  bool mMouseFocus;
  bool mKeyboardFocus;
  bool mFullscreen;
  bool mMinimized;
};

#endif
