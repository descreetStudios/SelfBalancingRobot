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
    Left,

    Count
  };

  Robot() = default;
  Robot(u32 a1, u32 a2, u32 aPWM,
        u32 b1, u32 b2, u32 bPWM)
    : mMotorA(a1, a2, aPWM), mMotorB(b1, b2, bPWM) {}

  void initialize() const;
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
