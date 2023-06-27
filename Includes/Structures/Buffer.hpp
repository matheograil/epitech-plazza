/*
** Project: ThePlazza
** File: Buffer.hpp
*/

#pragma once

#include "Core.hpp"

struct Buffer {
  long type;
  size_t size;
  char text[QUEUE_BUFFER_SIZE];
};
