/*
** Project: ThePlazza
** File: Utils.cpp
*/

#include "Core.hpp"

void Kitchen::addOrder(const Pizza &newOrder) {
  this->currentOrders.push_back(newOrder);
}

unsigned int Kitchen::getOrdersSize() const {
  return (this->currentOrders.size());
}

std::shared_ptr<Child> Kitchen::getProcess() const {
  return (this->process);
}

std::shared_ptr<Queue> Kitchen::getKitchenToReceptionQueue() const {
  return (this->kitchenToReceptionQueue);
}

std::shared_ptr<Queue> Kitchen::getReceptionToKitchenQueue() const {
  return (this->receptionToKitchenQueue);
}

void Kitchen::removeOrder(const Pizza &pizza) {
  for (unsigned int i = 0; i < this->currentOrders.size(); i++) {
    if (this->currentOrders[i].size == pizza.size && this->currentOrders[i].type == pizza.type) {
      this->currentOrders.erase(this->currentOrders.begin() + i);
      break;
    }
  }
}

std::chrono::time_point<std::chrono::system_clock> Kitchen::getLastTakenOrder() const {
  return (this->lastTakenOrder);
}

void Kitchen::setLastTakenOrder(const std::chrono::time_point<std::chrono::system_clock> &newLastTakenOrder) {
  this->lastTakenOrder = newLastTakenOrder;
}

std::vector<Pizza> Kitchen::getCurrentOrders() const {
  return (this->currentOrders);
}
