#include "Common.h"
#include "Motor.h"
#include "GY521.h"

class PID {
public:
  double Kp, Ki, Kd;
  double setpoint;

private:
  double integral = 0.0;
  double prevError = 0.0;

public:
  PID(double kp, double ki, double kd, double sp)
    : Kp(kp), Ki(ki), Kd(kd), setpoint(sp) {}

  double compute(double measured, double dt) {
    double error{ setpoint - measured };
    integral += error * dt;
    double derivative{ (error - prevError) / dt };
    prevError = error;

    // Anti-windup: limita l'integrale
    integral = constrain(integral, -50.0, 50.0);

    return Kp * error + Ki * integral + Kd * derivative;
  }

  void reset() {
    integral = 0.0;
    prevError = 0.0;
  }
};


struct Robot {
  Motor motorA{};
  Motor motorB{};

  Robot() = default;
  Robot(Motor& a, Motor& b)
    : motorA(a), motorB(b)
    {}

  void initialize()
  {
    motorA.initialize();
    motorB.initialize();
  }

  void run_forward()
  {
    motorA.run_forward();
    motorB.run_forward();
  }

  void run_backward()
  {
    motorA.run_backward();
    motorB.run_backward();
  }

  void stop()
  {
    motorA.stop();
    motorB.stop();
  }

  void update()
  {
    motorA.update();
    motorB.update();
  }
};

// Global objects
PID gPID(25.0, 0.8, 4.5, 0.0);
Robot gRobot{};
double gDT{ 0.0 };

// Engines pins
const int aPin1{ 7 };
const int aPin2{ 8 };
const int bPin1{ 12 };
const int bPin2{ 13 };
const int aPWM{ 5 };
const int bPWM{ 6 };

GY521 sensor(0x68);

void setup() {
  Logger::initialize();

  Logger::log("GY521_LIB_VERSION: ");
  Logger::log(GY521_LIB_VERSION);
  Logger::log("\n");

  Wire.begin();

  delay(100);
  while (sensor.wakeup() == false) {
    Logger::log(millis() + "ms");
    Logger::log("\tCould not connect to GY521: please check the GY521 address (0x68/0x69)\n");
    delay(1000);
  }

  // Sensor setup and calibration
  sensor.setAccelSensitivity(2);  //  8g
  sensor.setGyroSensitivity(1);   //  500 degrees/s
  sensor.setThrottle();
  sensor.calibrate(100, 0.0f, 0.0f, false);

  // Robot setup
  Motor a(7, 8, 5);
  Motor b(12, 13, 6);
  gRobot = Robot(a, b);
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

  // TEST
  gRobot.run_forward();

  gRobot.update();
}
