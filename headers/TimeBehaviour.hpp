//
// Created by Богдан Полянок on 21.09.2018.
//

#ifndef SMO_TIMEBEHAVIOUR_HPP
#define SMO_TIMEBEHAVIOUR_HPP

class TimeBehaviour {
public:
  virtual double generateTime(const double &intensity) = 0;
};

#endif //SMO_TIMEBEHAVIOUR_HPP
