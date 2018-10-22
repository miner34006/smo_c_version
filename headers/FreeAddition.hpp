//
// Created by Богдан Полянок on 05.10.2018.
//

#ifndef SMO_FREEADDITION_HPP
#define SMO_FREEADDITION_HPP

#include <vector>
#include <memory>

#include "AdditionStrategy.hpp"

class FreeAddition: public AdditionStrategy {
public:
  bool addApplication(std::vector<std::shared_ptr<Application>> &applications,
                      const std::shared_ptr<Application> &applicationToAdd);
};


#endif //SMO_FREEADDITION_HPP
