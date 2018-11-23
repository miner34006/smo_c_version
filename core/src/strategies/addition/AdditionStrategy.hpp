//
// Created by Богдан Полянок on 23.09.2018.
//

#ifndef SMO_ADDITIONSTRATEGY_HPP
#define SMO_ADDITIONSTRATEGY_HPP

#include <vector>
#include <memory>

#include <core/src/application/Application.hpp>

class AdditionStrategy;

using addition_strategy_ptr = std::shared_ptr<AdditionStrategy>;

class AdditionStrategy {
public:
  virtual bool addApplication(application_vector &applications,
                              const application_ptr &applicationToAdd) = 0;
};

#endif //SMO_ADDITIONSTRATEGY_HPP
