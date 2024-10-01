#include "../inc/tileMap.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <cstdio>
#include <fstream>
#include <string>

TileMap::TileMap(std::string path) {
  std::ifstream tileMapData(path);
  std::string line;
  std::string delimiter = ": ";

  std::getline(tileMapData, line);
  mNumTiles = std::stoi(line.substr(line.find(delimiter) + delimiter.length()));
  printf("NumTiles: %d\n", mNumTiles);

  std::getline(tileMapData, line);
  mTileMap =
      IMG_Load(line.substr(line.find(delimiter) + delimiter.length()).c_str());

  int id = 0;
  while (std::getline(tileMapData, line)) {
    line.erase(0, line.find(delimiter) + delimiter.length());
    SDL_Rect rect;
    std::string delimTwo = ", ";

    rect.x = std::stoi(line.substr(0, line.find(delimTwo)));
    line.erase(0, line.find(delimTwo) + delimTwo.length());
    rect.y = std::stoi(line.substr(0, line.find(delimTwo)));
    line.erase(0, line.find(delimTwo) + delimTwo.length());
    rect.w = std::stoi(line.substr(0, line.find(delimTwo)));
    line.erase(0, line.find(delimTwo) + delimTwo.length());
    rect.h = std::stoi(line.substr(0, line.find(delimTwo)));
    line.erase(0, line.find(delimTwo) + delimTwo.length());

    printf("Tile %d: %d, %d, %d, %d\n", id, rect.x, rect.y, rect.w, rect.h);
    mTileIDMap[id] = rect;
    id++;
  }
}

TileMap::~TileMap() {
  SDL_FreeSurface(mTileMap);
  mTileIDMap.clear();
  mNumTiles = 0;
}
