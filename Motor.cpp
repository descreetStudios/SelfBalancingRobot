#include "Motor.h"

void Motor::initialize() const {
  pinMode(mPin1, OUTPUT);
  pinMode(mPin2, OUTPUT);
}

void Motor::run_forward() {
  if (mState == Motor::State::Forward) return;
  digitalWrite(mPin1, LOW);
  mPWM = mPin2;
  mState = Motor::State::Forward;
}

void Motor::run_backward() {
  if (mState == Motor::State::Backward) return;
  digitalWrite(mPin1, HIGH);
  mPWM = mPin1;
  mState = Motor::State::Backward;
}

void Motor::stop() {
  if (mState == Motor::State::Stationary) return;
  digitalWrite(mPin1, LOW);
  digitalWrite(mPin2, LOW);
  mState = Motor::State::Stationary;
}

void Motor::update() const {
  analogWrite(mPWM, mPWMValue);
}

void Motor::set_pwm_value(s32 value) {
  mPWMValue = constrain(value, 0, 255);
}