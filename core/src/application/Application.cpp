//
// Created by Богдан Полянок on 21.09.2018.
//

#include "Application.hpp"

Application::Application(const size_t &sourceNumber, const double &timeOfCreation):
  sourceNumber_(sourceNumber),
  timeOfCreation_(timeOfCreation)
{
  if (timeOfCreation < 0) {
    throw std::invalid_argument("Invalid timeOfCreation (it must be more than 0)");
  }
}

size_t Application::getSourceIndex() const noexcept
{
  return sourceNumber_;
}

double Application::getTimeOfCreation() const noexcept
{
  return timeOfCreation_;
}
