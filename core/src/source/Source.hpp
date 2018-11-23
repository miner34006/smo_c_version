//
// Created by Богдан Полянок on 21.09.2018.
//

#ifndef SMO_SOURCE_HPP
#define SMO_SOURCE_HPP

#include <memory>
#include <stdexcept>

#include <core/src/strategies/timeBehavior/TimeBehaviour.hpp>

#include <vector>

class Source;
using source_ptr = std::shared_ptr<Source>;
using source_vector = std::vector<source_ptr>;

class Source {
public:
  Source(const double &intensity, const time_beh_ptr &timeBehaviour);

  double getPostTime() const noexcept;
  void setIntensity(const double &intensity);
  void cleanUp() noexcept;
  void postApplication() noexcept;

private:
  double postTime_;
  double intensity_;
  time_beh_ptr timeBehaviour_;
};

#endif //SMO_SOURCE_HPP
