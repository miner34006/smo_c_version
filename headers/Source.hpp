//
// Created by Богдан Полянок on 21.09.2018.
//

#ifndef SMO_SOURCE_HPP
#define SMO_SOURCE_HPP

#include <memory>
#include <stdexcept>

#include "TimeBehaviour.hpp"

class Source {
public:
  Source(const double &intensity, const std::shared_ptr<TimeBehaviour> &timeBehaviour);

  double getPostTime() const noexcept;
  void setIntensity(const double &intensity);
  void cleanUp() noexcept;
  void postApplication() noexcept;

private:
  double postTime_;
  double intensity_;
  std::shared_ptr<TimeBehaviour> timeBehaviour_;
};

#endif //SMO_SOURCE_HPP
