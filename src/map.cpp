#include "../inc/map.h"
#include <fstream>
#include <string>

const int numDiffTiles = 10;

void Map::loadMapFromFile(std::string path) {
  std::ifstream mapData(path);
  std::string line;
  std::string delimiter = " ";

  std::getline(mapData, line);
  std::string tileSetPath = line.substr(0, line.find(delimiter));
  line.erase(0, line.find(delimiter));
  mWidth = std::stoi(line.substr(0, line.find(delimiter)));
  mHeight = std::stoi(line.substr(line.find(delimiter) + delimiter.length()));

  mTileMap = new Tile[mWidth * mHeight];
  int currRow = 0;
  while (std::getline(mapData, line)) {
    for (int currCol = 0; currCol < mWidth; currCol++) {
      int tileRef = std::stoi(line.substr(0, line.find(delimiter)));
      line.erase(0, line.find(delimiter));
      // TODO: get tile id and rotation by id = ref%tileCount, rotation = ref-id
      // tileCount Load tile surface and blit to map surface
      int tileID = tileRef % numDiffTiles;
      int rotation = (tileRef - tileID) / numDiffTiles;
    }
  }
}
