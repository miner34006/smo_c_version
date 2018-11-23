//
// Created by Богдан Полянок on 21.09.2018.
//

#ifndef SMO_APPLICATION_HPP
#define SMO_APPLICATION_HPP

#include <memory>

#include <vector>

class Application;
using application_ptr = std::shared_ptr<Application>;
using application_vector = std::vector<application_ptr>;

class Application {
public:
  Application(const size_t &sourceNumber, const double &timeOfCreation);

  size_t getSourceIndex() const noexcept;
  double getTimeOfCreation() const noexcept;

private:
  size_t sourceNumber_;
  double timeOfCreation_;
};


#endif //SMO_APPLICATION_HPP
