/*
** Project: ThePlazza
** File: Parsing.hpp
*/

#pragma once

#include "Core.hpp"

class Parsing {
 public:
  struct parseStartingArgumentsRes {
    float multiplierCookingTime;
    unsigned int nbCooksPerKitchen;
    unsigned int reloadKitchenTime;
    bool error;
  };

  struct parsePromptRes {
    std::vector<Pizza> pizzas;
    bool error;
  };

  static parseStartingArgumentsRes parseStartingArguments(int, char **);
  static parsePromptRes parsePrompt(const std::string &);

 private:
  static std::vector<std::string> splitString(const std::string &, char);
  static std::vector<std::string> splitWords(const std::string &);
};
