//
// Created by Богдан Полянок on 23.09.2018.
//

#ifndef SMO_SELECTIONSTRATEGY_HPP
#define SMO_SELECTIONSTRATEGY_HPP

#include <vector>
#include <memory>
#include "Application.hpp"

class SelectionStrategy {
public:
  virtual std::shared_ptr<Application> removeApplication(std::vector<std::shared_ptr<Application>> &applications) = 0;
};

#endif //SMO_SELECTIONSTRATEGY_HPP
