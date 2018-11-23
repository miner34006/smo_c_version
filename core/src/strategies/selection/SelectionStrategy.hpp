//
// Created by Богдан Полянок on 23.09.2018.
//

#ifndef SMO_SELECTIONSTRATEGY_HPP
#define SMO_SELECTIONSTRATEGY_HPP

#include <vector>
#include <memory>

#include <core/src/application/Application.hpp>

class SelectionStrategy;

using selection_strategy_ptr = std::shared_ptr<SelectionStrategy>;

class SelectionStrategy {
public:
  virtual application_ptr removeApplication(application_vector &applications) = 0;
};

#endif //SMO_SELECTIONSTRATEGY_HPP
