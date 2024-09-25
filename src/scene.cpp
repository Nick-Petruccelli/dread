#include "../inc/scene.h"
#include <SDL2/SDL_events.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

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

void Scene::handelEvents(SDL_Event e) {
  mPlayer.handelEvents(e);
  for (unsigned int i = 0; i < mGameObjects.size(); i++) {
    mGameObjects[i]->handelEvents(e);
  }
}

void Scene::updateSceneState() {
  mPlayer.updateState();
  for (unsigned int i = 0; i < mGameObjects.size(); i++) {
    mGameObjects[i]->updateState();
  }
}

void Scene::renderScene() {
  mPlayer.render();
  for (unsigned int i = 0; i < mGameObjects.size(); i++) {
    mGameObjects[i]->render();
  }
}

unsigned int Scene::addGameObject(GameObject *obj) {
  obj->setID(mGameObjects.size());
  mGameObjects.push_back(obj);
  return obj->getID();
}

void Scene::removeGameObject(unsigned int objID) {
  unsigned int idx = getIndex(objID);
  std::swap(mGameObjects[idx], mGameObjects.back());
  mIndexLookUp[mGameObjects[idx]->getID()] = idx;
  mFreeIDs.push(objID);
}

unsigned int Scene::getIndex(unsigned int objID) { return mIndexLookUp[objID]; }
