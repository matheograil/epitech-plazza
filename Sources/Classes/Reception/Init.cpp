/*
** Project: ThePlazza
** File: Init.cpp
*/

#include "Core.hpp"

Reception::Reception(float multiplierCookingTime, unsigned int nbCooksPerKitchen, unsigned int reloadKitchenTime) {
  this->multiplierCookingTime = multiplierCookingTime;
  this->nbCooksPerKitchen = nbCooksPerKitchen;
  this->reloadKitchenTime = reloadKitchenTime;
}
