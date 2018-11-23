//
// Created by Богдан Полянок on 05.10.2018.
//

#ifndef SMO_FUNCTIONALMODULE_HPP
#define SMO_FUNCTIONALMODULE_HPP

#include <memory>

#include <core/src/source/Source.hpp>

#include <core/src/handler/Handler.hpp>

#include <core/src/buffer/Buffer.hpp>


struct simulationData {
  simulationData():
    refusedAppsCount(0),
    acceptedAppsCount(0),
    generatedAppsCount(0)
  {}

  void cleanUp(){
    refusedAppsCount = 0;
    acceptedAppsCount = 0;
    generatedAppsCount = 0;
  }

  size_t refusedAppsCount;
  size_t acceptedAppsCount;
  size_t generatedAppsCount;
};

class FunctionalModule {
public:
  explicit FunctionalModule(source_vector sources,
                   buffer_ptr buffer,
                   handlers_vector handlers);
  void simulate(const size_t &steps);
  void simulationStep();
  void cleanUp();

private:
  source_vector sources_;
  handlers_vector handlers_;
  buffer_ptr buffer_;
  size_t handlerPointer_;

  std::vector<simulationData> data_;

  int getNextHandler(const double &timeNow);

  void postFirstApplications();

  int getEarliestSourceIndex();
  int getEarliestHandlerIndex();
  std::pair<bool, int> getEarliestEvent();

  void handleCreationOfNewApplication(const size_t &sourceGeneratedApplication);
  void handleEndOfHandlerWork(const size_t &handlerFinishedWork);
};


#endif //SMO_FUNCTIONALMODULE_HPP
