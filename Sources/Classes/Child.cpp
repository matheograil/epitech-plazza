/*
** Project: ThePlazza
** File: Child.cpp
*/

#include "Core.hpp"

Child::Child() {
  this->pid = fork();
  if (this->pid == -1) {
    throw std::runtime_error("fork");
  }
}

bool Child::isChild() const {
  return (this->pid == 0);
}
