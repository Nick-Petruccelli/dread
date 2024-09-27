#include "../inc/ui.h"
#include <SDL2/SDL_ttf.h>
#include <cstddef>
#include <memory>

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

unsigned int UI::addTextElement(int x, int y, std::string text,
                                SDL_Color color) {
  std::shared_ptr<Texture> texture(new Texture());
  texture->setRenderer(gRenderer);
  if (!texture->loadFromText(mFont, text, color)) {
    return false;
  }
  unsigned int id;
  if (mFreeIDs.empty()) {
    id = mElements.size();
  } else {
    id = mFreeIDs.top();
    mFreeIDs.pop();
  }
  if (id >= mIndexLookUp.capacity()) {
    mIndexLookUp.reserve(id + 1 - mIndexLookUp.capacity());
  }

  mIndexLookUp[id] = mElements.size();
  mElements.emplace_back(x, y, texture);

  return id;
};

void UI::removeElement(unsigned int id) {
  unsigned int idx = getIndex(id);
  std::swap(mElements[idx], mElements.back());
  mElements.pop_back();
}

UI_Element *UI::getElement(unsigned int id) { return &mElements[getIndex(id)]; }

bool UI::setFont(std::string path) {
  if (mFont != NULL) {
    TTF_CloseFont(mFont);
    mFont = NULL;
  }
  mFont = TTF_OpenFont(path.c_str(), 28);
  return mFont != NULL;
}

void UI::setDebug(bool debug) { mDebug = debug; }

unsigned int UI::getIndex(unsigned int id) { return mIndexLookUp[id]; }

TTF_Font *UI::getFont() { return mFont; }
