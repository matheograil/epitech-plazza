/*
** Project: ThePlazza
** File: Run.cpp
*/

#include "Core.hpp"

void Kitchen::init() {
  std::cout << "I'm a new kitchen, nice to meet you!" << std::endl;
  this->currentOrdersMutex.lock();
  this->currentOrders.clear();
  this->currentOrdersMutex.unlock();
  this->lastStockReload = std::chrono::system_clock::now();

  // Stock initialization
  this->stock = {
      {Ingredient::DOE, 5},
      {Ingredient::TOMATO, 5},
      {Ingredient::GRUYERE, 5},
      {Ingredient::HAM, 5},
      {Ingredient::MUSHROOMS, 5},
      {Ingredient::STEAK, 5},
      {Ingredient::EGGPLANT, 5},
      {Ingredient::GOAT_CHEESE, 5},
      {Ingredient::CHIEF_LOVE, 5}
  };

  // Threads initialization
  for (unsigned int i = 0; i < this->nbCooksPerKitchen; i++) {
    this->cooks.emplace_back(&Kitchen::runCook, this);
  }
}

void Kitchen::run() {
  this->init();

  // Kitchen needs another thread to run
  std::thread kitchenThread(&Kitchen::runKitchen, this);

  // Joins all threads
  kitchenThread.join();
  for (auto &cook : this->cooks) {
    cook.join();
  }

  exit(0);
}

void Kitchen::runKitchen() {
  while (this->readInstruction()) {
    this->reloadStock();
  }

  // It also terminates cooks
  exit(0);
}

bool Kitchen::readInstruction() {
  // Every loop, we try to get a new instruction from the reception
  std::pair<std::vector<char>, bool> serial = this->getReceptionToKitchenQueue()->receiveMessage();
  if (!serial.second) {
    return (true);
  }

  Instruction instruction = Utils::deserializeInstructions(serial.first);

  // Exit instruction
  if (instruction.type == InstructionType::EXIT) {
    std::cout << "IPC: Kitchen <- Reception (I close)" << std::endl;
    return (false);
  }

  // Order instruction
  std::cout << "IPC: Kitchen <- Reception (received order)" << std::endl;
  this->currentOrdersMutex.lock();
  this->currentOrders.push_back(instruction.pizza);
  this->currentOrdersMutex.unlock();

  return (true);
}

void Kitchen::reloadStock() {
  if (std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - this->lastStockReload).count() < this->reloadKitchenTime) {
    return;
  }

  // Reloads the stock
  std::cout << "I'm a kitchen and I'm reloading my stock" << std::endl;
  this->stockMutex.lock();
  for (auto &ingredient : this->stock) {
    ingredient.second++;
  }
  this->stockMutex.unlock();

  this->lastStockReload = std::chrono::system_clock::now();
}
