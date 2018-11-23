//
// Created by Богдан Полянок on 05.10.2018.
//

#include "FreeAddition.hpp"

bool FreeAddition::addApplication(application_vector &applications,
                                  const application_ptr &applicationToAdd)
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
