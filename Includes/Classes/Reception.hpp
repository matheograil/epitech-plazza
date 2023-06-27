/*
** Project: ThePlazza
** File: Reception.hpp
*/

#pragma once

#include "Core.hpp"

class Reception {
 public:
  Reception(float, unsigned int, unsigned int);

  void run();
  void loadBalancing();

 private:
  unsigned int getAvailableSlots();
  void createProcesses(unsigned int);
  void distributeOrders();
  void readInstructions();
  void exitKitchenIfNecessary();
  void printStatus();
  static void printOrder(const Pizza &);

  float multiplierCookingTime;
  unsigned int nbCooksPerKitchen;
  unsigned int reloadKitchenTime;
  std::vector<Pizza> waitingOrders;
  std::vector<std::shared_ptr<Kitchen>> kitchens;
};
