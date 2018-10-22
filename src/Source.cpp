//
// Created by Богдан Полянок on 21.09.2018.
//

#include "../headers/Source.hpp"

Source::Source(const double &intensity, const std::shared_ptr<TimeBehaviour> &timeBehaviour):
  postTime_(0),
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

double Source::getPostTime() const noexcept
{
  return postTime_;
}

void Source::setIntensity(const double &intensity)
{
  if (intensity < 0) {
    throw std::invalid_argument("Invalid intensity (it must be more than 0)");
  }
  intensity_ = intensity;
}

void Source::cleanUp() noexcept
{
  postTime_ = 0;
}

void Source::postApplication() noexcept
{
  postTime_ += timeBehaviour_->generateTime(intensity_);
}
