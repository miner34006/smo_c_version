//
// Created by Богдан Полянок on 05.10.2018.
//

#ifndef SMO_FUNCTIONALMODULE_HPP
#define SMO_FUNCTIONALMODULE_HPP

#include <memory>

#include "Handler.hpp"
#include "Buffer.hpp"
#include "Source.hpp"

struct sourceData {
  sourceData():
    refusedAppsCount(0),
    acceptedAppsCount(0),
    generatedAppsCount(0),
    bufferingTime(0),
    handlingTime(0)
  {}

  void cleanUp(){
    refusedAppsCount = 0;
    acceptedAppsCount = 0;
    generatedAppsCount = 0;
    bufferingTime = 0;
    handlingTime = 0;
  }

  size_t refusedAppsCount;
  size_t acceptedAppsCount;
  size_t generatedAppsCount;

  double bufferingTime;
  double handlingTime;
};

struct handlerData {
  handlerData():
    workingTime(0)
  {}

  void cleanUp() {
    workingTime = 0;
  }

  double workingTime;
};

struct simulationData {
  simulationData(const size_t& sourcesCount, const size_t& handlersCount)
  {
    timeNow = 0;
    sourcesData = std::vector<sourceData>(sourcesCount);
    handlersData = std::vector<handlerData>(handlersCount);
  }

  void cleanUp() {
    for (size_t i = 0; i < sourcesData.size(); ++i) {
      sourcesData[i].cleanUp();
    }
    for (size_t i = 0; i < handlersData.size(); ++i) {
      handlersData[i].cleanUp();
    }
    timeNow = 0;
  }

  double getAverageTimeInSystem(const size_t& sourceIndex) {
    return getAverageHandlingTime(sourceIndex) + getAverageBufferingTime(sourceIndex);
  }

  double getAverageHandlingTime(const size_t& sourceIndex) {
    return sourcesData[sourceIndex].handlingTime / sourcesData[sourceIndex].acceptedAppsCount;
  }

  double getAverageBufferingTime(const size_t& sourceIndex) {
    return sourcesData[sourceIndex].bufferingTime / sourcesData[sourceIndex].acceptedAppsCount;
  }

  double getProbabilityOfFailure(const size_t& sourceIndex) {
    return sourcesData[sourceIndex].refusedAppsCount / sourcesData[sourceIndex].generatedAppsCount;
  }

  double getEmploymentRate(const size_t& handlerIndex) {
    return handlersData[handlerIndex].workingTime / timeNow;
  }

  std::vector<sourceData> sourcesData;
  std::vector<handlerData> handlersData;
  double timeNow;
};

class FunctionalModule {
public:
  explicit FunctionalModule(std::vector<std::shared_ptr<Source>> sources,
                   std::shared_ptr<Buffer> buffer,
                   std::vector<std::shared_ptr<Handler>> handlers);
  void simulate(const size_t &steps);
  void simulationStep();
  void cleanUp();

  simulationData data_;

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
