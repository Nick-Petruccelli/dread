#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HIGHT = 480;

class LTexture {
public:
  LTexture();
  ~LTexture();
  bool loadFromFile(std::string path);
  void free();
  void setColor(Uint8 r, Uint8 g, Uint8 b);
  void render(int x, int y, SDL_Rect *clip = NULL);
  int getWidth();
  int getHeight();

private:
  SDL_Texture *mTexture;
  int mWidth;
  int mHeight;
};

bool init();
bool loadMedia();
bool close();
SDL_Surface *loadSurface(std::string path);
SDL_Texture *loadTexture(std::string path);

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
LTexture gSpriteSheet;
SDL_Rect gSpriteClips[4];

int main(int argc, char *args[]) {
  if (!init()) {
    printf("ERROR::Failed to init\n");
    return -1;
  }
  if (!loadMedia()) {
    printf("ERROR::Failed to load media\n");
    return -1;
  }

  gSpriteSheet.setColor(255, 128, 128);
  SDL_Event e;
  bool quit = false;
  while (quit == false) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
    gSpriteSheet.render(0, 0, &gSpriteClips[0]);
    gSpriteSheet.render(380, 0, &gSpriteClips[1]);
    gSpriteSheet.render(380, 200, &gSpriteClips[2]);
    gSpriteSheet.render(0, 200, &gSpriteClips[3]);
    SDL_RenderPresent(gRenderer);
  }

  return 0;
}

bool init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDl::Failed to init video\n%s\n", SDL_GetError());
    return false;
  }

  gWindow = SDL_CreateWindow("DREAD", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                             SCREEN_HIGHT, SDL_WINDOW_SHOWN);
  if (gWindow == NULL) {
    printf("SDL::Failed to create window\n%s\n", SDL_GetError());
    return false;
  }

  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  if (gRenderer == NULL) {
    printf("SDL::Failed to create renderer\n%s\n", SDL_GetError());
    return false;
  }
  SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("ERROR::SDL::Failed to init image loading\n%s\n", SDL_GetError());
    return false;
  }
  // gSurface = SDL_GetWindowSurface(gWindow);

  return true;
}

bool loadMedia() {
  bool success = true;

  if (!gSpriteSheet.loadFromFile("assets/circles.png")) {
    printf("Failed to load spritesheet");
    return false;
  }
  gSpriteClips[0].x = 0;
  gSpriteClips[0].y = 0;
  gSpriteClips[0].w = 100;
  gSpriteClips[0].h = 100;

  gSpriteClips[1].x = 100;
  gSpriteClips[1].y = 0;
  gSpriteClips[1].w = 100;
  gSpriteClips[1].h = 100;

  gSpriteClips[2].x = 100;
  gSpriteClips[2].y = 100;
  gSpriteClips[2].w = 100;
  gSpriteClips[2].h = 100;

  gSpriteClips[3].x = 0;
  gSpriteClips[3].y = 100;
  gSpriteClips[3].w = 100;
  gSpriteClips[3].h = 100;

  return success;
}

SDL_Surface *loadSurface(std::string path) {
  SDL_Surface *surf = IMG_Load(path.c_str());
  if (surf == NULL) {
    printf("ERROR::SDL::Failed to load surface\n%s\n", SDL_GetError());
  }
  // surf = SDL_ConvertSurface(surf, gSurface->format, 0);
  return surf;
}

SDL_Texture *loadTexture(std::string path) {
  SDL_Texture *tex = NULL;
  SDL_Surface *surf = IMG_Load(path.c_str());
  if (surf == NULL) {
    printf("ERROR::SDL::Failed to load surface\n%s\n", SDL_GetError());
  }
  tex = SDL_CreateTextureFromSurface(gRenderer, surf);
  if (tex == NULL) {
    printf("ERROR::SDL::Failed to load texture\n%s\n", SDL_GetError());
  }
  return tex;
}

bool close() {
  gSpriteSheet.free();
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;
  IMG_Quit();
  SDL_Quit();

  return true;
}

LTexture::LTexture() {
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

LTexture::~LTexture() { free(); }

bool LTexture::loadFromFile(std::string path) {
  free();
  SDL_Texture *newTexture = NULL;
  SDL_Surface *surf = IMG_Load(path.c_str());
  if (surf == NULL) {
    printf("ERROR::SDL::Failed to load surface\n%s\n", SDL_GetError());
    return false;
  }
  SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0x0, 0xff, 0xff));
  newTexture = SDL_CreateTextureFromSurface(gRenderer, surf);
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

void LTexture::free() {
  if (mTexture != NULL) {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mHeight = 0;
    mWidth = 0;
  }
}

void LTexture::setColor(Uint8 r, Uint8 g, Uint8 b) {
  SDL_SetTextureColorMod(mTexture, r, g, b);
}

void LTexture::render(int x, int y, SDL_Rect *clip) {
  SDL_Rect displayRect = {x, y, mWidth, mHeight};
  if (clip != NULL) {
    displayRect.w = clip->w;
    displayRect.h = clip->h;
  }
  SDL_RenderCopy(gRenderer, mTexture, clip, &displayRect);
}

int LTexture::getWidth() { return mWidth; }

int LTexture::getHeight() { return mHeight; }
