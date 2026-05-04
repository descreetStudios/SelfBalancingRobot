#include "Common.h"
#include "Robot.h"
#include "GY521.h"
#include "AdvancedPID.h"

Robot gRobot;
GY521 gSensor(0x68);
// Kp, Ki, Kd, Kb
AdvancedPID gPID(30.0, 1.0, 7.0, 0.0);

void setup() {
  Logger::initialize(Logger::Level::Info, 2000000);

  Logger::log("GY521_LIB_VERSION: ");
  Logger::logln(GY521_LIB_VERSION);

  Wire.begin();
  Wire.setClock(400000);

  delay(100);
  while (gSensor.wakeup() == false) {
    Logger::log(millis() + "ms");
    Logger::logln("\tCould not connect to GY521: please check the GY521 address (0x68/0x69)");
    delay(1000);
  }

  // Sensor setup and calibration
  gSensor.setAccelSensitivity(2);  //  8g
  gSensor.setGyroSensitivity(1);   //  500 degrees/s
  gSensor.setThrottle();
  gSensor.calibrate(100, 0.0f, 0.0f, false);

  // Robot setup
  // 5, 6, 9, 10 driver
  gRobot = Robot(5, 6, /**/ 9, 10);
  gRobot.initialize();

  // PID setup
  gPID.setOutputLimits(-255.0, 255.0);
  gPID.setDerivativeFilter(0.8);
  gPID.setOutputRampRate(100.0);
}

const f32 SETPOINT{ -0.7f };
f32 gRoll{ 0.0f };
f32 gFeedForward{ 0.0f };
f32 gGyroRate{ 0.0f };

void loop() {
  gSensor.read();
  gRoll = gSensor.getRoll();
  if (gRoll > 180.0f) gRoll -= 360.0f;
  gGyroRate = gSensor.getGyroX();

  f32 output{ gPID.run(gRoll, SETPOINT, gFeedForward, gGyroRate) };

  if (output > 0)
    gRobot.run_backward();
  else if (output < 0)
    gRobot.run_forward();
  else
    gRobot.stop();
  
  Logger::log(abs(output));
  Logger::log(" ");
  Logger::log(gRoll);
  Logger::log(" ");
  Logger::log(gGyroRate);
  Logger::log(" ");
  Logger::logln(gFeedForward);

  //Logger::logln(millis());

  gRobot.set_pwm(abs(output));

  gRobot.update();
}
