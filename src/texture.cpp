#include "../inc/texture.h"
#include <SDL2/SDL_image.h>

Texture::Texture() {
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

Texture::Texture(SDL_Renderer *renderer) {
  mRenderer = renderer;
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

Texture::~Texture() { free(); }

bool Texture::loadFromFile(std::string path) {
  free();
  SDL_Texture *newTexture = NULL;
  SDL_Surface *surf = IMG_Load(path.c_str());
  if (surf == NULL) {
    printf("ERROR::SDL::Failed to load surface\n%s\n", SDL_GetError());
    return false;
  }
  SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0x0, 0xff, 0xff));
  newTexture = SDL_CreateTextureFromSurface(mRenderer, surf);
  if (newTexture == NULL) {
    printf("ERROR::SDL::Failed to create texture\n%s\n", SDL_GetError());
    return false;
  }
  mHeight = surf->h;
  mWidth = surf->w;
  SDL_FreeSurface(surf);
  mTexture = newTexture;

  return mTexture != NULL;
}

void Texture::free() {
  if (mTexture != NULL) {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mHeight = 0;
    mWidth = 0;
  }
}

void Texture::setRenderer(SDL_Renderer *renderer) { mRenderer = renderer; }

void Texture::setColor(Uint8 r, Uint8 g, Uint8 b) {
  SDL_SetTextureColorMod(mTexture, r, g, b);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
  SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::setAlpha(Uint8 a) { SDL_SetTextureAlphaMod(mTexture, a); }

void Texture::render(int x, int y, SDL_Rect *clip) {
  if (mRenderer == NULL) {
    printf("hit\n");
    return;
  }
  SDL_Rect displayRect = {x, y, mWidth, mHeight};
  if (clip != NULL) {
    displayRect.w = clip->w;
    displayRect.h = clip->h;
  }
  SDL_RenderCopy(mRenderer, mTexture, clip, &displayRect);
}

int Texture::getWidth() { return mWidth; }

int Texture::getHeight() { return mHeight; }

SDL_Texture *Texture::getTexturePtr() { return mTexture; }
SDL_Renderer *Texture::getRend() { return mRenderer; }
