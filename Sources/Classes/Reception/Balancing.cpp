/*
** Project: ThePlazza
** File: Balancing.cpp
*/

#include "Core.hpp"

/*
 * By taking into account the kitchens and the orders, returns the number of
 * available slots. To know if we need to create new kitchens or not.
 */
unsigned int Reception::getAvailableSlots() {
  unsigned int availableSlots = 0;

  for (auto &kitchen : this->kitchens) {
    availableSlots += (2 * this->nbCooksPerKitchen) - kitchen->getOrdersSize();
  }
  return (availableSlots);
}

/*
 * Allows to create new processes by using the Child class.
 * They will be added to the kitchens vector.
 */
void Reception::createProcesses(unsigned int processesNb) {
  unsigned int processesFailed = 0;

  for (unsigned int i = 0; i < processesNb; i++) {
    try {
      std::shared_ptr<Kitchen> kitchen =
          std::make_shared<Kitchen>(this->multiplierCookingTime, this->nbCooksPerKitchen, this->reloadKitchenTime);

      // Process redirection
      if (kitchen->getProcess()->isChild()) {
        kitchen->run();
      }

      this->kitchens.push_back(kitchen);
    } catch (std::runtime_error &e) {
      processesFailed++;
      continue;
    }
  }

  // If we failed to create some processes, we try again
  if (processesFailed > 0) {
    createProcesses(processesFailed);
  }
}

/*
 * The point here is to distribute the orders to the kitchens.
 */
void Reception::distributeOrders() {
  std::vector<char> serialLastOrder;
  Pizza lastOrder{};

  while (!this->waitingOrders.empty()) {
    for (const auto &kitchen : this->kitchens) {
      // If the kitchen is full, we skip it
      if (kitchen->getOrdersSize() >= (2 * this->nbCooksPerKitchen)) {
        continue;
      }

      lastOrder = this->waitingOrders.back();

      // Sends order to the kitchen
      serialLastOrder = Utils::serializeInstructions({
                                                         InstructionType::SEND_ORDER,
                                                         {
                                                             lastOrder.type,
                                                             lastOrder.size,
                                                         }
                                                     });
      if (!kitchen->getReceptionToKitchenQueue()->sendMessage(serialLastOrder)) {
        continue;
      }
      std::cout << "IPC: Reception -> Kitchen (cook order)" << std::endl;

      kitchen->addOrder(lastOrder);
      this->waitingOrders.pop_back();
    }
  }
}

/*
 * Takes the waiting orders and distributes them to the kitchens.
 * It creates new processes if needed.
 */
void Reception::loadBalancing() {
  unsigned int availableSlots = this->getAvailableSlots();
  unsigned int waitingOrdersSize = this->waitingOrders.size();

  // This section allows to allocate sufficient kitchens
  if (waitingOrdersSize > availableSlots) {
    unsigned int processesToCreate = (waitingOrdersSize - availableSlots) / (2 * this->nbCooksPerKitchen);

    // Rounds up
    if ((waitingOrdersSize - availableSlots) % (2 * this->nbCooksPerKitchen) != 0) {
      processesToCreate++;
    }

    std::cout << "Creating " << processesToCreate << " new kitchen(s)" << std::endl;
    this->createProcesses(processesToCreate);
  }

  this->distributeOrders();
  this->readInstructions();
  this->exitKitchenIfNecessary();
}

void Reception::readInstructions() {
  std::pair<std::vector<char>, bool> serial;
  Instruction instruction{};

  for (const auto &kitchen : this->kitchens) {
    // We try to get new instructions from the kitchen
    serial = kitchen->getKitchenToReceptionQueue()->receiveMessage();

    while (serial.second) {
      std::cout << "IPC: Reception <- Kitchen (order done)" << std::endl;
      instruction = Utils::deserializeInstructions(serial.first);
      kitchen->setLastTakenOrder(std::chrono::system_clock::now());
      kitchen->removeOrder(instruction.pizza);
      serial = kitchen->getKitchenToReceptionQueue()->receiveMessage();
    }
  }
}

void Reception::exitKitchenIfNecessary() {
  std::vector<char> serial;
  unsigned int i = 0;

  for (const auto &kitchen : this->kitchens) {
    if (kitchen->getOrdersSize() == 0 && std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now() - kitchen->getLastTakenOrder()).count() > 5) {
      // Sends exit instruction to the kitchen
      serial = Utils::serializeInstructions({
                                                InstructionType::EXIT,
                                                {}
                                            });
      while (!kitchen->getReceptionToKitchenQueue()->sendMessage(serial));
      std::cout << "IPC: Reception -> Kitchen (close it)" << std::endl;

      this->kitchens.erase(this->kitchens.begin() + i);

      return (this->exitKitchenIfNecessary()); // We need to call the function again because the vector has been modified
    }
    i++;
  }
}
