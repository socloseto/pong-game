#include <iostream>
#include <stdexcept>

#include "common/Game/Game.h"

int main() {
  try {
    Game game;
    game.run();
  } catch (const std::exception& e) {
    std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;

    return -1;
  } catch (...) {
    std::cerr << "Unknown error occurred!" << std::endl;
    return -2;
  }
  return 0;
}