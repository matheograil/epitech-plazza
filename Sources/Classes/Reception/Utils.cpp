/*
** Project: ThePlazza
** File: Utils.cpp
*/

#include "Core.hpp"

void Reception::printStatus() {
  unsigned int i = 1;

  std::cout << "------------ STATUS ------------" << std::endl;

  std::cout << "Waiting order(s): " << this->waitingOrders.size() << std::endl;
  for (auto const &order : this->waitingOrders) {
    Reception::printOrder(order);
  }

  std::cout << "------------" << std::endl;

  std::cout << "Opened kitchen(s): " << this->kitchens.size() << std::endl;
  for (auto const &kitchen : this->kitchens) {
    std::cout << std::endl << "Kitchen #" << i << ": " << kitchen->getOrdersSize() << " cooking pizza(s)" << std::endl;
    for (auto const &order : kitchen->getCurrentOrders()) {
      Reception::printOrder(order);
    }
    i++;
  }

  std::cout << "------------ END STATUS ------------" << std::endl;
}

void Reception::printOrder(const Pizza &order) {
  std::map<PizzaType, std::string> orderTypes = {
      {PizzaType::Regina, "Regina"},
      {PizzaType::Margarita, "Margarita"},
      {PizzaType::Americana, "Americana"},
      {PizzaType::Fantasia, "Fantasia"}
  };
  std::map<PizzaSize, std::string> orderSize = {
      {PizzaSize::S, "S"},
      {PizzaSize::M, "M"},
      {PizzaSize::L, "L"},
      {PizzaSize::XL, "XL"},
      {PizzaSize::XXL, "XXL"}
  };

  std::cout << "Order: " << orderTypes[order.type] << " " << orderSize[order.size] << " x1" << std::endl;
}
