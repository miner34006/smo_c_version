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
  FunctionalModule(const size_t &handlersCount, const size_t &sourcesCount);
  void doIteration();
  void cleanUp();


private:
  std::vector<std::shared_ptr<Handler>> handlers_;
  std::vector<std::shared_ptr<Source>> sources_;
  std::shared_ptr<Buffer> buffer_;

  size_t handlerPointer;

  // TODO add stats

  void createHandlers(const size_t &count);
  void createSources(const size_t &count);
  void createBuffer();

  int getNextHandler(const double &timeNow);

  void postFirstApplications();

  int getEarliestSourceIndex();
  int getEarliestHandlerIndex();
  std::pair<bool, int> getEarliestEvent();

  void handleCreationOfNewApplication(const size_t &sourceGeneratedApplication);
  void handleEndOfHandlerWork(const size_t &handlerFinishedWork);
};


#endif //SMO_FUNCTIONALMODULE_HPP
