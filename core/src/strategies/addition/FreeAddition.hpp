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
  bool addApplication(application_vector &applications,
                      const application_ptr &applicationToAdd);
};


#endif //SMO_FREEADDITION_HPP
