//
// Created by Богдан Полянок on 23.09.2018.
//

#include "../headers/RingSelection.hpp"

RingSelection::RingSelection():
  elementPointer_(0)
{}

std::shared_ptr<Application>
RingSelection::removeApplication(std::vector<std::shared_ptr<Application>> &applications)
{
  std::shared_ptr<Application> fromPointerToEnd = RingSelection::search(applications, elementPointer_, applications.size());
  if (fromPointerToEnd == nullptr) {
    return RingSelection::search(applications, 0, elementPointer_);
  } else {
    return fromPointerToEnd;
  }
}

void RingSelection::movePointer(const size_t &bufferSize, const size_t &pointerPosition)
{
  if (pointerPosition == bufferSize) {
    elementPointer_ = 0;
  } else {
    elementPointer_ = pointerPosition + 1;
  }
}

std::shared_ptr<Application> RingSelection::search(std::vector<std::shared_ptr<Application>> &applications,
                                                   const size_t &fromIndex, const size_t &toIndex) {
  for (size_t i = fromIndex; i < toIndex; i++) {
    if (applications[i] != nullptr) {
      const std::shared_ptr<Application> applicationToRemove = applications[i];
      applications[i] = nullptr;
      movePointer(applications.size(), i);
      return applicationToRemove;
    }
  }
  return nullptr;
}
