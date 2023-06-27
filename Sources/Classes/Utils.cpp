/*
** Project: ThePlazza
** File: Utils.cpp
*/

#include "Core.hpp"

std::vector<char> Utils::serializeInstructions(const Instruction &instruction) {
  std::vector<char> serialized;
  int type = instruction.type;
  int pizzaType = instruction.pizza.type;
  int pizzaSize = instruction.pizza.size;
  char buffer[12];

  std::memcpy(buffer, &type, sizeof(int));
  std::memcpy(buffer + 4, &pizzaType, sizeof(int));
  std::memcpy(buffer + 8, &pizzaSize, sizeof(int));

  serialized.insert(serialized.end(), buffer, buffer + 12);

  return (serialized);
}

Instruction Utils::deserializeInstructions(const std::vector<char> &serialized) {
  Instruction instruction{};
  int type, pizzaType, pizzaSize;

  std::memcpy(&type, serialized.data(), sizeof(int));
  std::memcpy(&pizzaType, serialized.data() + 4, sizeof(int));
  std::memcpy(&pizzaSize, serialized.data() + 8, sizeof(int));

  instruction.type = static_cast<InstructionType>(type);
  instruction.pizza.type = static_cast<PizzaType>(pizzaType);
  instruction.pizza.size = static_cast<PizzaSize>(pizzaSize);

  return (instruction);
}
