#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <map>
#include <string>

class TileMap {
public:
  TileMap(std::string path);
  ~TileMap();
  int getNumTiles();
  SDL_Surface getTileByID(int id);

private:
  int mNumTiles;
  std::map<int, SDL_Rect> mTileIDMap;
  SDL_Surface *mTileMap;
};
