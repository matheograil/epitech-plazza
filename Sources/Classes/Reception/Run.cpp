/*
** Project: ThePlazza
** File: Run.cpp
*/

#include "Core.hpp"

void Reception::run() {
  std::string prompt;
  Parsing::parsePromptRes parsedPrompt;
  std::future<std::string> noneBlockingGetLine;

  while (true) {
    // Allows to get a prompt without blocking
    noneBlockingGetLine = std::async(std::launch::async, []() {
      std::string prompt;

      std::getline(std::cin, prompt);
      return (prompt);
    });

    // If the user doesn't enter anything, we load balance waiting orders
    while (noneBlockingGetLine.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
      this->loadBalancing();
    }

    // Now we can get the prompt
    prompt = noneBlockingGetLine.get();

    // Exits
    if (prompt == "exit") {
      break;
    }

    // Status
    if (prompt == "status") {
      this->printStatus();
      continue;
    }

    // Handles new orders
    parsedPrompt = Parsing::parsePrompt(prompt);
    if (parsedPrompt.error) {
      std::cout << "Invalid arguments, orders cancelled" << std::endl;
      continue;
    }
    std::cout << "The order has been taken (waiting status)" << std::endl;
    for (const auto &order : parsedPrompt.pizzas) {
      this->waitingOrders.push_back(order);
    }

    this->loadBalancing();
  }
}
