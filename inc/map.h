#pragma once

#include "texture.h"
#include <string>
enum TileType { WALKABLE, WALL, HAZARD };

struct Tile {};

class Map {
public:
  void loadMapFromFile(std::string path);
  TileType getTileType(int x, int y);
  Texture *getTexture();

private:
  Texture mTexture;
  Tile *mTileMap;
  int mWidth;
  int mHeight;
};
