#include <iostream>
#include "common/Game/Game.h"
#ifdef _MSC_VER
#include <SFML/Main.hpp>
#endif

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