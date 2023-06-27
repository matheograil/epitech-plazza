/*
** Project: ThePlazza
** File: Parsing.cpp
*/

#include "Core.hpp"

Parsing::parseStartingArgumentsRes Parsing::parseStartingArguments(int ac, char **av) {
  parseStartingArgumentsRes res = {0, 0, 0, true};

  if (ac != 4) {
    return (res);
  }

  try {
    // First argument handling
    float multiplierCookingTime = std::stof(av[1]);
    if (multiplierCookingTime < 0) {
      return (res);
    }
    res.multiplierCookingTime = multiplierCookingTime;

    // Second argument handling. We cannot have less than 1 cook per kitchen
    float nbCooksPerKitchen = std::stof(av[2]);
    if (nbCooksPerKitchen < 1) {
      return (res);
    }
    res.nbCooksPerKitchen = (unsigned int) nbCooksPerKitchen;

    // Third argument handling
    float reloadKitchenTime = std::stof(av[3]);
    if (reloadKitchenTime < 0) {
      return (res);
    }
    res.reloadKitchenTime = (unsigned int) reloadKitchenTime;
  } catch (const std::exception &e) {
    return (res);
  }

  res.error = false;
  return (res);
}

std::vector<std::string> Parsing::splitString(const std::string &input, char delimiter) {
  std::vector<std::string> res;
  size_t start = 0;
  size_t end = input.find(delimiter);

  while (end != std::string::npos) {
    res.push_back(input.substr(start, end - start));
    start = end + 1;
    end = input.find(delimiter, start);
  }
  res.push_back(input.substr(start));
  return (res);
}

std::vector<std::string> Parsing::splitWords(const std::string &input) {
  std::string word;
  std::vector<std::string> res;
  std::istringstream iss(input);

  while (iss >> word) {
    res.push_back(word);
  }
  return (res);
}

std::unordered_map<std::string, PizzaType> pizzaTypes = {
    {"regina", PizzaType::Regina},
    {"margarita", PizzaType::Margarita},
    {"americana", PizzaType::Americana},
    {"fantasia", PizzaType::Fantasia}
};

std::unordered_map<std::string, PizzaSize> pizzaSizes = {
    {"S", PizzaSize::S},
    {"M", PizzaSize::M},
    {"L", PizzaSize::L},
    {"XL", PizzaSize::XL},
    {"XXL", PizzaSize::XXL}
};

Parsing::parsePromptRes Parsing::parsePrompt(const std::string &input) {
  parsePromptRes res = {{}, true};
  std::vector<std::string> orders = Parsing::splitString(input, ';');
  float number;
  std::vector<std::string> words;

  for (const auto &order : orders) {
    words = Parsing::splitWords(order);

    // 3 words expected
    if (words.size() != 3 || words[2].length() < 1) {
      return (res);
    }

    // Gets the number of pizzas
    try {
      number = std::stof(words[2].substr(1));
    } catch (const std::exception &e) {
      return (res);
    }

    // Checks the pizza name, size and number
    if (pizzaSizes.find(words[1]) == pizzaSizes.end() || pizzaTypes.find(words[0]) == pizzaTypes.end()
        || words[2][0] != 'x' || number < 1) {
      return (res);
    }

    for (unsigned int i = 0; i < (unsigned int) number; i++) {
      res.pizzas.push_back({pizzaTypes[words[0]], pizzaSizes[words[1]]});
    }
  }

  res.error = false;
  return (res);
}
