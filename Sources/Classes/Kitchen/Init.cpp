/*
** Project: ThePlazza
** File: Init.cpp
*/

#include "Core.hpp"

Kitchen::Kitchen(float multiplierCookingTime, unsigned int nbCooksPerKitchen, unsigned int reloadKitchenTime) {
  this->process = std::make_shared<Child>();
  this->kitchenToReceptionQueue = std::make_shared<Queue>();
  this->receptionToKitchenQueue = std::make_shared<Queue>();
  this->lastTakenOrder = std::chrono::system_clock::now();
  this->multiplierCookingTime = multiplierCookingTime;
  this->nbCooksPerKitchen = nbCooksPerKitchen;
  this->reloadKitchenTime = reloadKitchenTime;
}
