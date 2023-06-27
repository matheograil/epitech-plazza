/*
** Project: ThePlazza
** File: Utils.hpp
*/

#pragma once

#include "Core.hpp"

class Utils {
 public:
  static std::vector<char> serializeInstructions(const Instruction &);
  static Instruction deserializeInstructions(const std::vector<char> &);
};
