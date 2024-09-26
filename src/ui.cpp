#include "../inc/ui.h"
#include <SDL2/SDL_ttf.h>
#include <cstddef>

extern SDL_Renderer *gRenderer;

UI::~UI() {
  for (size_t i = 0; i < mElements.size(); i++) {
    mElements[i].texture->free();
  }
  mElements.clear();
  mElements.shrink_to_fit();
}

void UI::render() {
  for (size_t i = 0; i < mElements.size(); i++) {
    UI_Element elm = mElements[i];
    elm.texture->render(elm.x, elm.y);
  }
}

bool UI::addTextElement(int x, int y, std::string text, SDL_Color color) {
  static Texture texture;
  texture.setRenderer(gRenderer);
  if (!texture.loadFromText(mFont, text, color)) {
    return false;
  }
  mElements.emplace_back(x, y, &texture);
  return true;
};

bool UI::setFont(std::string path) {
  if (mFont != NULL) {
    TTF_CloseFont(mFont);
    mFont = NULL;
  }
  mFont = TTF_OpenFont(path.c_str(), 28);
  return mFont != NULL;
}

void UI::setDebug(bool debug) { mDebug = debug; }
