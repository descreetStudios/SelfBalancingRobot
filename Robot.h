#ifndef ROBOT_H
#define ROBOT_H

#include "Motor.h"

class Robot {
public:
  enum class State {
    Stationary,
    Forward,
    Backward,
    Right,
    Left
  };

  Robot() = default;
  Robot(u32 a1, u32 a2,
        u32 b1, u32 b2)
    : mMotorA(a1, a2), mMotorB(b1, b2) {}

  void initialize() const;
  void set_pwm(s32 pwm);
  void run_forward();
  void run_backward();
  void turn_right();
  void turn_left();
  void stop();
  void update() const;

  [[nodiscard]] Motor get_motor_a() const { return mMotorA; }
  [[nodiscard]] Motor get_motor_b() const { return mMotorB; }
  [[nodiscard]] State get_state() const { return mState; }

private:
  Motor mMotorA;
  Motor mMotorB;
  State mState{ State::Stationary };
};

#endif  // !defined(ROBOT_H)
