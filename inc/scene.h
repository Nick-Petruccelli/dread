#ifndef SCENE_H
#define SCENE_H

#include "gameObject.h"
#include "player.h"
#include <stack>
#include <string>
#include <vector>

class Scene {
public:
  Scene(SDL_Renderer *renderer);
  ~Scene();
  bool addPlayer(std::string name);
  void removePlayer();
  unsigned int addGameObject(GameObject *obj);
  void removeGameObject(unsigned int objID);
  void handelEvents(SDL_Event e);
  void updateSceneState();
  void renderScene();

private:
  unsigned int getIndex(unsigned int objID);

  SDL_Renderer *mRenderer;
  Player mPlayer;
  std::vector<GameObject *> mGameObjects;
  std::vector<unsigned int> mIndexLookUp;
  std::stack<unsigned int> mFreeIDs;
};

#endif
