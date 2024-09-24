#include "../inc/scene.h"

Scene::Scene() {
  mGameObjects.reserve(20);
  mIndexLookUp.reserve(20);
}

void Scene::renderScene() {
  for (unsigned int i = 0; i < mGameObjects.size(); i++) {
    mGameObjects[i].render();
  }
}

unsigned int Scene::addGameObject(GameObject obj) {
  if (mFreeIDs.empty()) {
    obj.setID(mGameObjects.back().getID() + 1);
  } else {
    obj.setID(mFreeIDs.top());
    mFreeIDs.pop();
  }
  mGameObjects.push_back(obj);
  mIndexLookUp[obj.getID()] = mGameObjects.size() - 1;
  return obj.getID();
}

void Scene::removeGameObject(unsigned int objID) {
  unsigned int idx = getIndex(objID);
  std::swap(mGameObjects[idx], mGameObjects.back());
  mIndexLookUp[mGameObjects[idx].getID()] = idx;
  mFreeIDs.push(objID);
}

unsigned int Scene::getIndex(unsigned int objID) { return mIndexLookUp[objID]; }
