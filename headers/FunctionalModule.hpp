//
// Created by Богдан Полянок on 05.10.2018.
//

#ifndef SMO_FUNCTIONALMODULE_HPP
#define SMO_FUNCTIONALMODULE_HPP

#include <memory>

#include "Handler.hpp"
#include "Buffer.hpp"
#include "Source.hpp"

class FunctionalModule {
public:
  explicit FunctionalModule(std::vector<std::shared_ptr<Source>> sources,
                   std::shared_ptr<Buffer> buffer,
                   std::vector<std::shared_ptr<Handler>> handlers);
  void simulate(const size_t &steps);
  void simulationStep();
  void cleanUp();

private:
  std::vector<std::shared_ptr<Source>> sources_;
  std::vector<std::shared_ptr<Handler>> handlers_;
  std::shared_ptr<Buffer> buffer_;
  size_t handlerPointer_;

  int getNextHandler(const double &timeNow);

  void postFirstApplications();

  int getEarliestSourceIndex();
  int getEarliestHandlerIndex();
  std::pair<bool, int> getEarliestEvent();

  void handleCreationOfNewApplication(const size_t &sourceGeneratedApplication);
  void handleEndOfHandlerWork(const size_t &handlerFinishedWork);
};


#endif //SMO_FUNCTIONALMODULE_HPP
