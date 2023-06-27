/*
** Project: RayTracer
** File: Main.cpp
*/

#include "Core.hpp"

int main(int ac, char **av) {
  std::srand(std::time(nullptr));
  Parsing::parseStartingArgumentsRes args = Parsing::parseStartingArguments(ac, av);

  if (args.error) {
    std::cerr << "Incorrect arguments" << std::endl;
    return (84);
  }

  // Starts the reception
  Reception reception = Reception(args.multiplierCookingTime, args.nbCooksPerKitchen, args.reloadKitchenTime);
  reception.run();

  return (0);
}
