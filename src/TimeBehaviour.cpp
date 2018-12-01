//
// Created by Богдан Полянок on 21.09.2018.
//

#include <stdexcept>
#include "../headers/TimeBehaviour.hpp"

double ExponentialTimeBehavior::generateTime(const double &intensity) {
  if (intensity < 0) {
    throw std::invalid_argument("Intensity should be > 0");
  }
  const double randomValue = ((double) std::rand() / (RAND_MAX));
  return 1 - std::exp(-(randomValue / intensity));
}

double InfiniteUniformTimeBehavior::generateTime(const double &intensity) {
  if (intensity < 0) {
    throw std::invalid_argument("Intensity should be > 0");
  }
  double randomValue = ((double) std::rand() / (RAND_MAX));
  return a_ + randomValue * (b_ - a_);
}

InfiniteUniformTimeBehavior::InfiniteUniformTimeBehavior(const double &a, const double &b):
  a_(a),
  b_(b)
{
  if (b < a){
    throw std::invalid_argument("b should be more than a");
  }
}
