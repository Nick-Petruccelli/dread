#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Texture {
public:
  Texture();
  Texture(SDL_Renderer *renderer);
  ~Texture();
  void setRenderer(SDL_Renderer *renderer);
  bool loadFromFile(std::string path);
  bool loadFromText(TTF_Font *font, std::string text, SDL_Color color);
  void free();
  void setColor(Uint8 r, Uint8 g, Uint8 b);
  void setBlendMode(SDL_BlendMode blending);
  void setAlpha(Uint8 a);
  void render(int x, int y, int *camOffSet = NULL, SDL_Rect *clip = NULL);
  int getWidth();
  int getHeight();
  bool isLoaded();
  SDL_Texture *getTexturePtr();
  SDL_Renderer *getRend();

private:
  SDL_Renderer *mRenderer;
  SDL_Texture *mTexture;
  int mWidth;
  int mHeight;
};

#endif
