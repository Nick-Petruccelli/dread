#ifndef SCENE_H
#define SCENE_H

#include "gameObject.h"
#include <stack>
#include <vector>

class Scene {
public:
  Scene();
  unsigned int addGameObject(GameObject obj);
  void removeGameObject(unsigned int objID);
  void renderScene();

private:
  unsigned int getIndex(unsigned int objID);

  std::vector<GameObject> mGameObjects;
  std::vector<unsigned int> mIndexLookUp;
  std::stack<unsigned int> mFreeIDs;
};

#endif
