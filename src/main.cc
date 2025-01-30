#include <warpframe/logger/logger.h>
#include <warpframe/util/constant.h>
#include <warpframe/window/window.h>

#include <iostream>

int main() {
  Logger::init();
  Logger::getLogger()->info("WarpFrame initialized.");

  Window window(DEF_WINDOW_WIDTH, DEF_WINDOW_HEIGHT, TITLE);

  // basic render loop
  while (!window.shouldClose()) {
    window.clear();

    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}
