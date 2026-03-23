#include "Common.h"
#include "Robot.h"
#include "GY521.h"

Robot gRobot;
GY521 gSensor(0x68);

void setup() {
  Logger::initialize();

  Logger::log("GY521_LIB_VERSION: ");
  Logger::logln(GY521_LIB_VERSION);

  Wire.begin();

  delay(100);
  while (gSensor.wakeup() == false) {
    Logger::log(millis() + "ms");
    Logger::logln("\tCould not connect to GY521: please check the GY521 address (0x68/0x69)");
    delay(1000);
  }

  // Sensor setup and calibration
  sensor.setAccelSensitivity(2);  //  8g
  sensor.setGyroSensitivity(1);   //  500 degrees/s
  sensor.setThrottle();
  sensor.calibrate(100, 0.0f, 0.0f, false);

  // Robot setup
  gRobot = Robot(7, 8, 5, /**/ 12, 13, 6);
  gRobot.initialize();
}

void loop() {
  /*
  // Read sensor and get pitch
  sensor.read();
  float pitch = sensor.getPitch();
  gRobot.angle = pitch;

  Serial.println(pitch, 1);

  // Calculate PID
  gDT = millis() - gDT;
  double output = pid.compute(gRobot.angle, gDT);
  output = std::clamp(output, -255.0, 255.0);

  gRobot.update(output, gDT);

  Serial.println(output, 3);
  */

  // Print sensor info
  gSensor.read();
  f32 pitch{gSensor.getPitch()};
  Logger::log("Pitch: ");
  Logger::logln(pitch);

  // TEST
  gRobot.run_forward();

  gRobot.update();
}
