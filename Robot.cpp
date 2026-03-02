#include "Robot.h"

void Robot::initialize() const {
  mMotorA.initialize();
  mMotorB.initialize();
}

void Robot::run_forward() {
  if (mState == Robot::State::Forward) return;
  mMotorA.run_forward();
  mMotorB.run_forward();
  mState = Robot::State::Forward;
}

void Robot::run_backward() {
  if (mState == Robot::State::Backward) return;
  mMotorA.run_backward();
  mMotorB.run_backward();
  mState = Robot::State::Backward;
}

void Robot::turn_right() {
  if (mState == Robot::State::Right) return;
  mMotorA.run_forward();
  mMotorB.run_backward();
  mState = Robot::State::Right;
}

void Robot::turn_left() {
  if (mState == Robot::State::Left) return;
  mMotorA.run_backward();
  mMotorB.run_forward();
  mState = Robot::State::Left;
}

void Robot::stop() {
  if (mState == Robot::State::Stationary) return;
  mMotorA.stop();
  mMotorB.stop();
  mState = Robot::State::Stationary;
}

void Robot::update() const {
  mMotorA.update();
  mMotorB.update();
}