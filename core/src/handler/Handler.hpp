//
// Created by Богдан Полянок on 21.09.2018.
//

#ifndef SMO_HANDLER_HPP
#define SMO_HANDLER_HPP

#include <memory>
#include <stdexcept>
#include <vector>

#include <core/src/strategies/timeBehavior/TimeBehaviour.hpp>

class Handler;
using handler_ptr = std::shared_ptr<Handler>;
using handlers_vector = std::vector<handler_ptr>;

class Handler {
public:
  Handler(const double &intensity, const time_beh_ptr &timeBehaviour);

  double getFinishTime() const noexcept;
  void setIntensity(const double &intensity);
  void cleanUp() noexcept;
  double handleApplication(const double &arrivalTime);
  bool isWorking(const double &timeNow);

private:
  double finishTime_;
  double intensity_;
  time_beh_ptr timeBehaviour_;
};

#endif //SMO_HANDLER_HPP
