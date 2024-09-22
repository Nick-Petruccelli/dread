#ifndef ENGINE_H
#define ENGINE_H

struct Engine {
public:
  static void init();
  static unsigned int getDeltaTime();
  static unsigned int getScreenWidth();
  static unsigned int getScreenHeight();
  static void updateDeltaTime();

private:
  static unsigned int mDeltaTime;
  static unsigned int mPrevFrameTime;
  static unsigned int mScreenWidth;
  static unsigned int mScreenHeight;
};

#endif
