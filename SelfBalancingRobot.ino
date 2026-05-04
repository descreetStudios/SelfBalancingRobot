#include "Common.h"
#include "Robot.h"
#include "AdvancedPID.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Robot gRobot;
Adafruit_MPU6050 gSensor;
// Kp, Ki, Kd, Kb
AdvancedPID gPID(10.0, 0.2, 2.5, 1.5);

void setup() {
  Logger::initialize(Logger::Level::Info, 115200);

  Wire.begin();
  Wire.setClock(100000);

  delay(100);
  while (!gSensor.begin()) {
    Logger::log(millis() + "ms");
    Logger::logln("\tCould not connect to Gyro Sensor: please check the address (0x68/0x69)");
    delay(1000);
  }

  // Robot setup
  // 5, 6, 9, 10 driver
  gRobot = Robot(5, 6, /**/ 9, 10);
  gRobot.initialize();

  // PID setup
  gPID.setOutputLimits(-255.0, 255.0);
  gPID.setDerivativeFilter(0.1);
  //gPID.setOutputRampRate(500.0);

  delay(200);
}

const f32 SETPOINT{ 0.0f };
f32 gRoll{ 0.0f };
f32 gFeedForward{ 0.0f };
f32 gGyroRate{ 0.0f };

void loop() {
  static long lastTime{ 0 };
  unsigned long currentTime{ micros() };
  float dt{ (currentTime - lastTime) / 1000000.0f };
  lastTime = currentTime;

  sensors_event_t a, g, temp;
  gSensor.getEvent(&a, &g, &temp);
  float ay = a.acceleration.y;
  float az = a.acceleration.z;
  float accelAngle = atan2(a.acceleration.y, a.acceleration.z) * RAD_TO_DEG;
  gGyroRate = g.gyro.x * RAD_TO_DEG;

  if (dt <= 0 || dt > 0.02f) dt = 0.01f;

  const float alpha = 0.995f;

  gRoll = alpha * (gRoll + gGyroRate * dt) +
          (1.0f - alpha) * accelAngle;


  f32 output{ gPID.run(gRoll, SETPOINT, gFeedForward, gGyroRate) };

  if (output > 0)
    gRobot.run_backward();
  else if (output < 0)
    gRobot.run_forward();

  Logger::log(abs(output));
  Logger::log(" ");
  Logger::log(gRoll);
  Logger::log(" ");
  Logger::logln(gGyroRate);

  gRobot.set_pwm(abs(output));
  gRobot.update();
}
