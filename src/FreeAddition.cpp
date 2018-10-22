//
// Created by Богдан Полянок on 05.10.2018.
//

#include "../headers/FreeAddition.hpp"

bool FreeAddition::addApplication(std::vector<std::shared_ptr<Application>> &applications,
                                  const std::shared_ptr<Application> &applicationToAdd)
{
  for (auto &application : applications) {
    if (application == nullptr) {
      // TODO will it replace element, check it!
      application = applicationToAdd;
      return true;
    }
  }
  return false;
}