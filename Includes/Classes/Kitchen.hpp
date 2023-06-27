/*
** Project: ThePlazza
** File: Kitchen.hpp
*/

#pragma once

#include "Core.hpp"

class Kitchen {
 public:
  Kitchen(float, unsigned int, unsigned int);

  void run();
  void addOrder(const Pizza &);
  void removeOrder(const Pizza &);
  unsigned int getOrdersSize() const;
  std::shared_ptr<Child> getProcess() const;
  std::shared_ptr<Queue> getKitchenToReceptionQueue() const;
  std::shared_ptr<Queue> getReceptionToKitchenQueue() const;
  std::chrono::time_point<std::chrono::system_clock> getLastTakenOrder() const;
  void setLastTakenOrder(const std::chrono::time_point<std::chrono::system_clock> &);
  std::vector<Pizza> getCurrentOrders() const;

 private:
  std::shared_ptr<Queue> kitchenToReceptionQueue;
  std::shared_ptr<Queue> receptionToKitchenQueue;
  std::shared_ptr<Child> process;
  std::vector<Pizza> currentOrders;
  std::chrono::time_point<std::chrono::system_clock> lastTakenOrder;
  std::map<Ingredient, unsigned int> stock;
  std::mutex stockMutex;
  std::mutex currentOrdersMutex;
  std::vector<std::thread> cooks;
  float multiplierCookingTime;
  unsigned int nbCooksPerKitchen;
  unsigned int reloadKitchenTime;
  std::chrono::time_point<std::chrono::system_clock> lastStockReload;

  bool readInstruction();
  void init();
  void runCook();
  void runKitchen();
  void reloadStock();
  bool consumeStock(const Pizza &);
  void confirmOrder(const Pizza &) const;
  void waitCooking(const Pizza &) const;
};
