#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "gameObject.h"
#include "player.h"
#include "texture.h"
#include <stack>
#include <string>
#include <vector>

class Scene {
public:
  Scene();
  Scene(SDL_Renderer *renderer);
  ~Scene();
  bool addPlayer(std::string name);
  bool addMap(std::string name);
  void removePlayer();
  unsigned int addGameObject(int x, int y, std::string texturePath);
  void removeGameObject(unsigned int objID);
  void handelEvents(SDL_Event e);
  void updateSceneState();
  void renderScene();

  int getMapWidth();
  int getMapHeight();

private:
  unsigned int getIndex(unsigned int objID);

  SDL_Renderer *mRenderer;
  Camera mCamera;
  Player mPlayer;
  Texture mMap;
  std::vector<GameObject> mGameObjects;
  std::vector<unsigned int> mIndexLookUp;
  std::stack<unsigned int> mFreeIDs;
};

#endif
