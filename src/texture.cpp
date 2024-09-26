#include "../inc/texture.h"
#include "../inc/window.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

extern Window gWindow;
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

bool Texture::loadFromText(TTF_Font *font, std::string text, SDL_Color color) {
  free();
  SDL_Surface *surf = TTF_RenderText_Solid(font, text.c_str(), color);
  if (surf == NULL) {
    printf("ERROR::SDL::Failed to load surface\n%s\n", SDL_GetError());
    return false;
  }
  mTexture = SDL_CreateTextureFromSurface(mRenderer, surf);
  if (mTexture == NULL) {
    printf("ERROR::SDL::Failed to create texture\n%s\n", SDL_GetError());
    return false;
  }
  mHeight = surf->h;
  mWidth = surf->w;
  SDL_FreeSurface(surf);
  return true;
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

void Texture::render(int x, int y, int *camOffSet, SDL_Rect *clip) {
  if (mRenderer == NULL) {
    printf("hit\n");
    return;
  }
  if (camOffSet == NULL) {
    camOffSet = new int[2];
    camOffSet[0] = 0;
    camOffSet[1] = 0;
  }
  float windowScale = gWindow.getScale();
  SDL_Rect displayRect = {(int)((x - camOffSet[0]) * windowScale),
                          (int)((y - camOffSet[1]) * windowScale),
                          (int)(mWidth * windowScale),
                          (int)(mHeight * windowScale)};
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
