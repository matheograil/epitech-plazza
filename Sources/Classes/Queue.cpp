/*
** Project: ThePlazza
** File: Queue.cpp
*/

#include "Core.hpp"

Queue::Queue() {
  this->key = std::rand();

  this->id = msgget(key, 0666 | IPC_CREAT);
  if (this->id == -1) {
    throw std::runtime_error("msgget");
  }
}

Queue::~Queue() {
  msgctl(this->id, IPC_RMID, nullptr);
}

bool Queue::sendMessage(const std::vector<char> &message) const {
  Buffer buffer{};

  buffer.type = 1;
  buffer.size = message.size();
  std::memcpy(buffer.text, message.data(), message.size());
  if (msgsnd(this->id, &buffer, sizeof(buffer), IPC_NOWAIT) == -1) {
    return (false);
  }
  return (true);
}

std::pair<std::vector<char>, bool> Queue::receiveMessage() const {
  Buffer buffer{};

  if (msgrcv(this->id, &buffer, sizeof(buffer), 1, IPC_NOWAIT) == -1) {
    return (std::make_pair(std::vector<char>{}, false));
  }
  return (std::make_pair(std::vector<char>(buffer.text, buffer.text + buffer.size), true));
}
