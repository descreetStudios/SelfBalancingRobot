#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include "Types.h"

namespace Logger {

enum class Level {
  Trace,
  Info,
  Warning,
  Error,

  Count
};

extern Level gLevel;

void initialize(Level level = Level::Info, u32 channel = 9600);
void log(const String& msg, Level level = Level::Info);
void logln(const String& msg, Level level = Level::Info);
void set_level(Level level);

}  // Logger namespace

#endif  // !defined(LOGGER_H)