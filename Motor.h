#ifndef MOTOR_H
#define MOTOR_H

#include "Common.h"

class Motor {
public:
  enum class State {
    Stationary,
    Forward,
    Backward,

    Count
  };

  Motor() = default;
  Motor(u32 pin1, u32 pin2, u32 pwmPin)
    : mPin1(pin1), mPin2(pin2), mPWM(pwmPin) {}

  void initialize() const;
  void run_forward();
  void run_backward();
  void stop();
  void update() const;

  // NOTE: This methor requires the PWM value to be normalized
  void set_pwm_value(s32 value);

  [[nodiscard]] const s32 get_pwm_value() const {
    return mPWMValue;
  }
  [[nodiscard]] const State get_state() const {
    return mState;
  }

private:
  u32 mPin1{ 0 };
  u32 mPin2{ 0 };
  u32 mPWM{ 0 };
  s32 mPWMValue{ 0 };
  State mState{ State::Stationary };
};

#endif  // !defined(MOTOR_H)
