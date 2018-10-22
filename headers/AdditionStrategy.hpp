//
// Created by Богдан Полянок on 23.09.2018.
//

#ifndef SMO_ADDITIONSTRATEGY_HPP
#define SMO_ADDITIONSTRATEGY_HPP

#include <vector>
#include <memory>

#include "Application.hpp"

class AdditionStrategy {
public:
  virtual bool addApplication(std::vector<std::shared_ptr<Application>> &applications,
                              const std::shared_ptr<Application> &applicationToAdd) = 0;
};

#endif //SMO_ADDITIONSTRATEGY_HPP
