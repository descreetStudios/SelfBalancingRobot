#include "Logger.h"

namespace Logger {

Level gLevel{ Level::Info };

namespace {

const char* level_to_cstring(Logger::Level level) {
  switch (level) {
    case Logger::Level::Trace: return "TRACE";
    case Logger::Level::Info: return "INFO";
    case Logger::Level::Warning: return "WARN";
    case Logger::Level::Error: return "ERROR";
  }
  return "UNKNOWN";
}

}  // anonymous namespace

void initialize(Level level, u32 channel) {
  gLevel = level;
  Serial.begin(channel);
  Serial.println();
}

void set_level(Level level) {
  gLevel = level;
}

void log(const String& msg, Level level) {
  if (level < gLevel) return;

  String levelStr = String(level_to_cstring(level));
  String output = "[" + levelStr + "] " + msg;
  Serial.print(output);
}

void logln(const String& msg, Level level) {
  if (level < gLevel) return;

  String levelStr = String(level_to_cstring(level));
  String output = "[" + levelStr + "] " + msg;
  Serial.println(output);
}

}  // Logger namespace