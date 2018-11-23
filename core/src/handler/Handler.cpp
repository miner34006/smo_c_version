//
// Created by Богдан Полянок on 21.09.2018.
//

#include "Handler.hpp"

Handler::Handler(const double &intensity, const std::shared_ptr<TimeBehaviour> &timeBehaviour):
  finishTime_(0),
  intensity_(intensity),
  timeBehaviour_(timeBehaviour)
{
  if (intensity < 0) {
    throw std::invalid_argument("Invalid intensity (it must be more than 0)");
  }
  if (!timeBehaviour) {
    throw std::invalid_argument("Invalid timeBehaviour ptr");
  }
}

double Handler::getFinishTime() const noexcept
{
  return finishTime_;
}

void Handler::setIntensity(const double &intensity)
{
  if (intensity < 0) {
    throw std::invalid_argument("Invalid intensity (it must be more than 0)");
  }
  intensity_ = intensity;
}

void Handler::cleanUp() noexcept
{
  finishTime_ = 0;
}

double Handler::handleApplication(const double &arrivalTime)
{
  if (arrivalTime < 0) {
    throw std::invalid_argument("Invalid arrivalTime (it must be more than 0)");
  }
  const double workingTime = timeBehaviour_->generateTime(intensity_);
  finishTime_ = arrivalTime + workingTime;
  return workingTime;
}

bool Handler::isWorking(const double &timeNow) {
  return timeNow < getFinishTime();
}
