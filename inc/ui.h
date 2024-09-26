#ifndef UI_H
#define UI_H

#include "texture.h"
#include <SDL2/SDL_ttf.h>
#include <vector>

struct UI_Element {
  int x;
  int y;
  Texture *texture;

  UI_Element(int x, int y, Texture *texture) : x(x), y(y), texture(texture) {}
};

class UI {
public:
  ~UI();
  void render();
  bool addTextElement(int x, int y, std::string text, SDL_Color color);
  bool addImgElement(std::string path);
  bool setFont(std::string path);
  void setDebug(bool debug);

private:
  std::vector<struct UI_Element> mElements;
  TTF_Font *mFont = NULL;
  bool mDebug;
};

#endif
