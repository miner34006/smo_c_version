//
// Created by Богдан Полянок on 23.09.2018.
//

#ifndef SMO_BUFFER_HPP
#define SMO_BUFFER_HPP

#include <memory>

#include <core/src/strategies/selection/SelectionStrategy.hpp>
#include <core/src/strategies/addition/AdditionStrategy.hpp>

class Buffer;
using buffer_ptr = std::shared_ptr<Buffer>;

class Buffer {
public:
  Buffer(const selection_strategy_ptr &selectionStrategy,
         const addition_strategy_ptr &additionStrategy,
         const size_t &bufferSize);

  bool addApplication(const application_ptr &application);
  application_ptr removeApplication();

  size_t getApplicationQuantity(const size_t &sourceIndex) const;
  bool isEmpty() const;
  bool isFull() const;
  void cleanUp();

  application_ptr replaceApplication(const application_ptr &applicationToInsert);

private:
  selection_strategy_ptr selectionStrategy_;
  addition_strategy_ptr additionStrategy_;
  application_vector applications_;
  size_t bufferSize_;
  size_t freeSlots_;
};

#endif //SMO_BUFFER_HPP
