/*
** Project: ThePlazza
** File: Queue.hpp
*/

#pragma once

#include "Core.hpp"

class Queue {
 public:
  Queue();
  ~Queue();

  bool sendMessage(const std::vector<char> &) const;
  std::pair<std::vector<char>, bool> receiveMessage() const;

 private:
  key_t key;
  int id;
};
