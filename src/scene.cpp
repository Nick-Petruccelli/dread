#include "../inc/scene.h"
#include <SDL2/SDL_events.h>
#include <fstream>
#include <string>

Scene::Scene() { mRenderer = NULL; }

Scene::Scene(SDL_Renderer *renderer) {
  mRenderer = renderer;
  mGameObjects.reserve(20);
  mIndexLookUp.reserve(20);
}

Scene::~Scene() {}

bool Scene::addPlayer(std::string path) {
  std::ifstream playerData(path);
  std::string line;
  std::string delimiter = ": ";
  while (std::getline(playerData, line)) {
    std::string param = line.substr(0, line.find(delimiter));
    std::string value = line.substr(line.find(delimiter) + delimiter.length());

    if (param.compare("Texture") == 0) {
      mPlayer.setTexture(value, mRenderer);
    } else if (param.compare("MaxVel") == 0) {
      mPlayer.setMaxVel(std::stof(value));
    }
  }
  playerData.close();
  return true;
}

bool Scene::addMap(std::string path) {
  mMap.setRenderer(mRenderer);
  return mMap.loadFromFile(path);
}

void Scene::handelEvents(SDL_Event e) {
  mPlayer.handelEvents(e);
  for (unsigned int i = 0; i < mGameObjects.size(); i++) {
    mGameObjects[i].handelEvents(e);
  }
}

void Scene::updateSceneState() {
  mPlayer.updateState();
  mCamera.moveTo(mPlayer.getPosX() + mPlayer.getWidth() / 2.0,
                 mPlayer.getPosY() + mPlayer.getHeight() / 2.0);
  for (unsigned int i = 0; i < mGameObjects.size(); i++) {
    mGameObjects[i].updateState();
  }
}

void Scene::renderScene() {
  int *camOffSet = mCamera.getOffSet();
  mMap.render(0, 0, camOffSet);
  mPlayer.render(camOffSet);
  for (unsigned int i = 0; i < mGameObjects.size(); i++) {
    mGameObjects[i].render(camOffSet);
  }
  delete camOffSet;
}

unsigned int Scene::addGameObject(int x, int y, std::string texturePath) {
  unsigned int id;
  if (mFreeIDs.empty()) {
    id = mGameObjects.size();
  } else {
    id = mFreeIDs.top();
    mFreeIDs.pop();
  }
  if (id >= mIndexLookUp.size()) {
    mIndexLookUp.reserve(1);
  }
  mIndexLookUp[id] = mGameObjects.size();
  mGameObjects.emplace_back(x, y);
  mGameObjects.back().setTexture(texturePath, mRenderer);

  return id;
}

void Scene::removeGameObject(unsigned int objID) {
  unsigned int idx = getIndex(objID);
  std::swap(mGameObjects[idx], mGameObjects.back());
  mIndexLookUp[mGameObjects[idx].getID()] = idx;
  mFreeIDs.push(objID);
}

int Scene::getMapWidth() { return mMap.getWidth(); }

int Scene::getMapHeight() { return mMap.getHeight(); }

unsigned int Scene::getIndex(unsigned int objID) { return mIndexLookUp[objID]; }
