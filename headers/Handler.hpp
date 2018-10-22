//
// Created by Богдан Полянок on 21.09.2018.
//

#ifndef SMO_HANDLER_HPP
#define SMO_HANDLER_HPP

#include <memory>
#include <stdexcept>

#include "TimeBehaviour.hpp"

class Handler {
public:
  Handler(const double &intensity, const std::shared_ptr<TimeBehaviour> &timeBehaviour);

  double getFinishTime() const noexcept;
  void setIntensity(const double &intensity);
  void cleanUp() noexcept;
  double handleApplication(const double &arrivalTime);
  bool isWorking(const double &timeNow);

private:
  double finishTime_;
  double intensity_;
  std::shared_ptr<TimeBehaviour> timeBehaviour_;
};

#endif //SMO_HANDLER_HPP
