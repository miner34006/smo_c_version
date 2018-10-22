//
// Created by Богдан Полянок on 23.09.2018.
//

#ifndef SMO_BUFFER_HPP
#define SMO_BUFFER_HPP

#include <memory>

#include "Application.hpp"
#include "SelectionStrategy.hpp"
#include "AdditionStrategy.hpp"

class Buffer {
public:
  Buffer(const std::shared_ptr<SelectionStrategy> &selectionStrategy,
         const std::shared_ptr<AdditionStrategy> &additionStrategy,
         const size_t &bufferSize);

  bool addApplication(const std::shared_ptr<Application> &application);
  std::shared_ptr<Application> removeApplication();

  size_t getApplicationQuantity(const size_t &sourceIndex) const;
  bool isEmpty() const;
  bool isFull() const;
  void cleanUp();

  std::shared_ptr<Application> replaceApplication(const std::shared_ptr<Application> &applicationToInsert);

private:
  std::shared_ptr<SelectionStrategy> selectionStrategy_;
  std::shared_ptr<AdditionStrategy> additionStrategy_;
  std::vector<std::shared_ptr<Application>> applications_;
  size_t bufferSize_;
  size_t freeSlots_;
};

#endif //SMO_BUFFER_HPP
