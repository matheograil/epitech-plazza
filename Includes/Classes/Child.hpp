/*
** Project: ThePlazza
** File: Child.hpp
*/

#pragma once

#include "Core.hpp"

class Child {
 public:
  Child();

  bool isChild() const;

 private:
  pid_t pid;
};
