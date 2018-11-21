//
// Created by Богдан Полянок on 21.09.2018.
//

#include <stdexcept>
#include "../headers/TimeBehaviour.hpp"

double ExponentialTimeBehavior::generateTime(const double &intensity) {
  // TODO: add time generation strategy
  if (intensity < 0) {
    throw std::invalid_argument("Intensity should be > 0");
  }
  const double randomValue = ((double) std::rand() / (RAND_MAX));
  return std::log(1  + std::exp(-intensity * randomValue)) / -intensity;
}

double InfiniteUniformTimeBehavior::generateTime(const double &intensity) {
  // TODO: add time generation strategy
  if (intensity < 0) {
    throw std::invalid_argument("Intensity should be > 0");
  }
  const double randomValue = ((double) std::rand() / (RAND_MAX));
  return 0;
}

InfiniteUniformTimeBehavior::InfiniteUniformTimeBehavior(const double &a, const double &b):
  a_(a),
  b_(b)
{}
