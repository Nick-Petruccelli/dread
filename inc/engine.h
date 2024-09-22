#ifndef ENGINE_H
#define ENGINE_H

class Engine {
public:
  static unsigned int getDeltaTime();
  static unsigned int getScreenWidth();
  static unsigned int getScreenHeight();

private:
  void updateDeltaTime();
  unsigned int deltaTime;
  unsigned int prevTime;
  unsigned int screenWidth;
  unsigned int screenHeight;
};

#endif
