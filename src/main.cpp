#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
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
  void setBlendMode(SDL_BlendMode blending);
  void setAlpha(Uint8 a);
  void render(int x, int y, SDL_Rect *clip = NULL);
  int getWidth();
  int getHeight();

private:
  SDL_Texture *mTexture;
  int mWidth;
  int mHeight;
};

class Player {
public:
  Player();
  bool setTexture(std::string path);
  void eventHandler(SDL_Event e);
  void updateState();
  void move();
  void render();
  void getPosition();
  void getVelocity();

private:
  int mPosX;
  int mPosY;
  int mVelX;
  int mVelY;
  int mMaxVel;
  LTexture mTexture;
};

bool init();
bool loadMedia();
bool close();
void updateDelta();
SDL_Surface *loadSurface(std::string path);
SDL_Texture *loadTexture(std::string path);

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
LTexture gBackround;
LTexture gPlayer;
Uint32 deltaTime = 0;
Uint32 lastFrameTime = 0;

int main(int argc, char *args[]) {
  if (!init()) {
    printf("ERROR::Failed to init\n");
    return -1;
  }
  if (!loadMedia()) {
    printf("ERROR::Failed to load media\n");
    return -1;
  }

  Player p = Player();
  p.setTexture("assets/character.png");

  SDL_Event e;
  bool quit = false;
  Uint8 alpha = 255;
  while (quit == false) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      p.eventHandler(e);
    }
    updateDelta();
    p.updateState();
    gBackround.render(0, 0);
    gPlayer.render(0, 0);
    p.render();
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

  if (!gBackround.loadFromFile("assets/backround.png")) {
    printf("Failed to load spritesheet");
    return false;
  }
  if (!gPlayer.loadFromFile("assets/character.png")) {
    printf("Failed to load character");
    return false;
  }
  gBackround.setBlendMode(SDL_BLENDMODE_BLEND);
  gPlayer.setBlendMode(SDL_BLENDMODE_BLEND);

  return success;
}

void updateDelta() {
  deltaTime = SDL_GetTicks() - lastFrameTime;
  lastFrameTime = SDL_GetTicks();
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
  gBackround.free();
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

void LTexture::setBlendMode(SDL_BlendMode blending) {
  SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 a) { SDL_SetTextureAlphaMod(mTexture, a); }

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

Player::Player() {
  mPosX = 100;
  mPosY = 150;
  mVelX = 0;
  mVelY = 0;
  mMaxVel = 1;
}

void Player::eventHandler(SDL_Event e) {
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
    case SDLK_w:
      mVelY -= mMaxVel;
      break;
    case SDLK_s:
      mVelY += mMaxVel;
      break;
    case SDLK_a:
      mVelX -= mMaxVel;
      break;
    case SDLK_d:
      mVelX += mMaxVel;
      break;
    };
  } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
    case SDLK_w:
      mVelY += mMaxVel;
      break;
    case SDLK_s:
      mVelY -= mMaxVel;
      break;
    case SDLK_a:
      mVelX += mMaxVel;
      break;
    case SDLK_d:
      mVelX -= mMaxVel;
      break;
    };
  }
}

void Player::move() {
  int velAdjustX = mVelX * deltaTime;
  int velAdjustY = mVelY * deltaTime;
  mPosX += velAdjustX;
  mPosY += velAdjustY;

  if (mPosX < 0 || mPosX > SCREEN_WIDTH - mTexture.getWidth()) {
    mPosX -= velAdjustX;
  }
  if (mPosY < 0 || mPosY > SCREEN_HIGHT - mTexture.getHeight()) {
    mPosY -= velAdjustY;
  }
}

void Player::updateState() { move(); }

void Player::render() { mTexture.render(mPosX, mPosY); }

bool Player::setTexture(std::string path) {
  if (!mTexture.loadFromFile("assets/character.png")) {
    printf("Failed to load character");
    return false;
  }
  return true;
}
