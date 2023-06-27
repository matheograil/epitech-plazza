/*
** Project: ThePlazza
** File: Cook.cpp
*/

#include "Core.hpp"

void Kitchen::runCook() {
  std::cout << "I'm a new cook" << std::endl;

  while (true) {
    this->currentOrdersMutex.lock();
    if (this->currentOrders.empty()) {
      this->currentOrdersMutex.unlock();
      continue;
    }

    Pizza order = this->currentOrders[0];

    // Removes the order from the list
    this->currentOrders.erase(this->currentOrders.begin());
    this->currentOrdersMutex.unlock();

    // Checks if we have enough ingredients
    this->stockMutex.lock();
    if (!this->consumeStock(order)) {
        this->stockMutex.unlock();
        this->currentOrdersMutex.lock();
        this->currentOrders.push_back(order);
        this->currentOrdersMutex.unlock();
        continue;
    }
    this->stockMutex.unlock();

    // Waits for the cooking time
    this->waitCooking(order);

    // Sends the order to the reception
    this->confirmOrder(order);
  }
}

bool Kitchen::consumeStock(const Pizza &order) {
  std::map<PizzaType, std::vector<Ingredient>> pizzaIngredients = {
      {PizzaType::Margarita, {Ingredient::DOE, Ingredient::TOMATO, Ingredient::GRUYERE}},
      {PizzaType::Regina,
       {Ingredient::DOE, Ingredient::TOMATO, Ingredient::GRUYERE, Ingredient::HAM, Ingredient::MUSHROOMS}},
      {PizzaType::Americana, {Ingredient::DOE, Ingredient::TOMATO, Ingredient::GRUYERE, Ingredient::STEAK}},
      {PizzaType::Fantasia,
       {Ingredient::DOE, Ingredient::TOMATO, Ingredient::EGGPLANT, Ingredient::GOAT_CHEESE, Ingredient::CHIEF_LOVE}}
  };

  // Checks if we have enough ingredients
  for (const auto &ingredient : pizzaIngredients[order.type]) {
    if (this->stock[ingredient] == 0) {
      return (false);
    }
  }

  // Consumes ingredients
  for (const auto &ingredient : pizzaIngredients[order.type]) {
    this->stock[ingredient] -= 1;
  }

  return (true);
}

void Kitchen::confirmOrder(const Pizza &order) const {
  std::vector<char> serial = Utils::serializeInstructions({
                                                              InstructionType::CONFIRM_ORDER,
                                                              {
                                                                  order.type,
                                                                  order.size
                                                              }
                                                          });

  while (!this->getKitchenToReceptionQueue()->sendMessage(serial));
  std::cout << "IPC: Kitchen -> Reception (order done)" << std::endl;
}

void Kitchen::waitCooking(const Pizza &order) const {
  std::map<PizzaType, unsigned int> pizzaDuration = {
      {PizzaType::Margarita, 1 * this->multiplierCookingTime},
      {PizzaType::Regina, 2 * this->multiplierCookingTime},
      {PizzaType::Americana, 2 * this->multiplierCookingTime},
      {PizzaType::Fantasia, 4 * this->multiplierCookingTime}
  };

  // Waits for the pizza to be cooked
  std::cout << "I'm a kitchen and I'm waiting for the pizza to be cooked" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(pizzaDuration[order.type]));
}
