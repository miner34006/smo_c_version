//
// Created by Богдан Полянок on 23.09.2018.
//

#include "../headers/Buffer.hpp"

Buffer::Buffer(const std::shared_ptr<SelectionStrategy> &selectionStrategy,
               const std::shared_ptr<AdditionStrategy> &additionStrategy,
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

bool Buffer::addApplication(const std::shared_ptr<Application> &application) {
  const bool successAddition = additionStrategy_->addApplication(applications_, application);
  if (successAddition) {
    freeSlots_--;
  }
  return successAddition;
}

std::shared_ptr<Application> Buffer::removeApplication() {
  const std::shared_ptr<Application> removedApplication = selectionStrategy_->removeApplication(applications_);
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

std::shared_ptr<Application> Buffer::replaceApplication(const std::shared_ptr<Application> &applicationToInsert) {
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

  std::shared_ptr<Application> applicationToReturn = applications_[lastApplicationIndex];
  applications_[lastApplicationIndex] = applicationToInsert;

  return applicationToReturn;
}
