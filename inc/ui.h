#ifndef UI_H
#define UI_H

#include "texture.h"
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <stack>
#include <vector>

struct UI_Element {
  int x;
  int y;
  std::shared_ptr<Texture> texture;

  UI_Element(int x, int y, std::shared_ptr<Texture> texture)
      : x(x), y(y), texture(texture) {}
};

class UI {
public:
  ~UI();
  void render();
  unsigned int addTextElement(int x, int y, std::string text, SDL_Color color);
  unsigned int addImgElement(std::string path);
  void removeElement(unsigned int id);
  bool setFont(std::string path);
  void setDebug(bool debug);
  UI_Element *getElement(unsigned int id);
  TTF_Font *getFont();

private:
  std::vector<struct UI_Element> mElements;
  unsigned int getIndex(unsigned int id);
  std::stack<unsigned int> mFreeIDs;
  std::vector<unsigned int> mIndexLookUp;
  TTF_Font *mFont = NULL;
  bool mDebug;
};

#endif
