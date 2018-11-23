//
// Created by Богдан Полянок on 23.09.2018.
//

#include "Buffer.hpp"

Buffer::Buffer(const selection_strategy_ptr &selectionStrategy,
               const addition_strategy_ptr &additionStrategy,
               const size_t &bufferSize):
  selectionStrategy_(selectionStrategy),
  additionStrategy_(additionStrategy),
  bufferSize_(bufferSize),
  freeSlots_(bufferSize)
{
  if (!selectionStrategy) {
    throw std::invalid_argument("Invalid selectionStrategy ptr");
  }
  if (!additionStrategy) {
    throw std::invalid_argument("Invalid additionStrategy ptr");
  }
  applications_.resize(bufferSize, nullptr);
}

bool Buffer::addApplication(const application_ptr &application) {
  const bool successAddition = additionStrategy_->addApplication(applications_, application);
  if (successAddition) {
    freeSlots_--;
  }
  return successAddition;
}

application_ptr Buffer::removeApplication() {
  const application_ptr removedApplication = selectionStrategy_->removeApplication(applications_);
  if (removedApplication != nullptr) {
    freeSlots_++;
  }
  return removedApplication;
}

bool Buffer::isEmpty() const {
  for (const auto &application : applications_) {
    if (application != nullptr) {
      return false;
    }
  }
  return true;
}

bool Buffer::isFull() const {
  for (const auto &application : applications_) {
    if (application == nullptr) {
      return false;
    }
  }
  return true;
}

void Buffer::cleanUp() {
  freeSlots_ = applications_.size();
  for (auto &application : applications_) {
    application = nullptr;
  }
}

size_t Buffer::getApplicationQuantity(const size_t &sourceIndex) const {
  size_t applicationQuantity = 0;
  for (auto &application : applications_) {
    if (application->getSourceIndex() == sourceIndex) {
      applicationQuantity++;
    }
  }
  return applicationQuantity;
}

application_ptr Buffer::replaceApplication(const application_ptr &applicationToInsert) {
  if (! isFull()) {
    throw std::logic_error("Buffer is not full, use addAplication() instead replaceApplication()");
  }

  double lastApplicationTime = -1;
  size_t lastApplicationIndex = 0;
  for (size_t i = 0; i < applications_.size(); ++i) {
    if (applications_[i]->getTimeOfCreation() > lastApplicationTime) {
      lastApplicationTime = applications_[i]->getTimeOfCreation();
      lastApplicationIndex = i;
    }
  }

  application_ptr applicationToReturn = applications_[lastApplicationIndex];
  applications_[lastApplicationIndex] = applicationToInsert;

  return applicationToReturn;
}
