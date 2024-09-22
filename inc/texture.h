#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string>

class Texture {
public:
  Texture();
  Texture(SDL_Renderer *renderer);
  ~Texture();
  void setRenderer(SDL_Renderer *renderer);
  bool loadFromFile(std::string path);
  void free();
  void setColor(Uint8 r, Uint8 g, Uint8 b);
  void setBlendMode(SDL_BlendMode blending);
  void setAlpha(Uint8 a);
  void render(int x, int y, SDL_Rect *clip = NULL);
  int getWidth();
  int getHeight();
  bool isLoaded();

private:
  SDL_Renderer *mRenderer;
  SDL_Texture *mTexture;
  int mWidth;
  int mHeight;
};

#endif
