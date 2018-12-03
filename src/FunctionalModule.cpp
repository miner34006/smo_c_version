//
// Created by Богдан Полянок on 05.10.2018.
//

#include "../headers/FunctionalModule.hpp"

void FunctionalModule::cleanUp() {
  data_.cleanUp();
  buffer_->cleanUp();
  for (auto &source : sources_) {
    source->cleanUp();
  }
  for (auto &handler : handlers_) {
    handler->cleanUp();
  }

  handlerPointer_ = 0;
}

void FunctionalModule::postFirstApplications() {
  for (size_t i = 0; i < sources_.size(); ++i) {
    sources_[i]->postApplication();
    data_.sourcesData[i].generatedAppsCount ++;
  }
}

int FunctionalModule::getEarliestSourceIndex() {
  double minTime = -1;
  int sourceIndex = -1;

  for (int i = 0; i < sources_.size(); i++) {
    if ((sourceIndex == -1) || (sources_[i]->getPostTime() < minTime)) {
      minTime = sources_[i]->getPostTime();
      sourceIndex = i;
    }
  }
  return sourceIndex;
}


int FunctionalModule::getEarliestHandlerIndex() {
  double minTime = -1;
  int handlerIndex = -1;

  for (int i = 0; i < handlers_.size(); i++) {
    if ((handlerIndex == -1) || (handlers_[i]->getFinishTime() < minTime)) {
      minTime = handlers_[i]->getFinishTime();
      handlerIndex = i;
    }
  }
  return handlerIndex;
}

std::pair<bool, int> FunctionalModule::getEarliestEvent() {
  // <true, index> - source with index
  // <false, index> - handler with index

  const int earliestSourceIndex = getEarliestSourceIndex();
  const double sourceTime = sources_[earliestSourceIndex]->getPostTime();

  const int earliestHandlerIndex = getEarliestHandlerIndex();
  const double handlerTime = handlers_[earliestHandlerIndex]->getFinishTime();

  if (sourceTime < handlerTime) {
    return {true, earliestSourceIndex};
  } else {
    return {false, earliestHandlerIndex};
  }
}

void FunctionalModule::handleCreationOfNewApplication(const size_t &sourceGeneratedApplication) {
  auto application = std::make_shared<Application>(sourceGeneratedApplication, sources_[sourceGeneratedApplication]->getPostTime());

  // Add application to buffer [Add in buffer behavior]
  const bool hasAdded = buffer_->addApplication(application);
  if (!hasAdded) {
    // Не добавили заявку в буфер -> заменяем заявку [Refuse strategy]
    std::shared_ptr<Application> replacedApplication = buffer_->replaceApplication(application);
    data_.sourcesData[replacedApplication->getSourceIndex()].refusedAppsCount++;
    // TODO учитываем статистику для выброшенной зявки (а надо ли????????)
  }
  sources_[sourceGeneratedApplication]->postApplication();
  data_.sourcesData[sourceGeneratedApplication].generatedAppsCount ++;
  // TODO Учет статистики (среднее число apps в буфере)
}

void FunctionalModule::handleEndOfHandlerWork(const size_t &handlerFinishedWork) {
  std::shared_ptr<Application> application;
  if (!buffer_->isEmpty()) {
    // TODO Для учета статистики (время работы в приборе)
    application = buffer_->removeApplication();
    const int nextHandlerIndex = getNextHandler(handlers_[handlerFinishedWork]->getFinishTime());
    const double timeInHandler = handlers_[nextHandlerIndex]->handleApplication(handlers_[handlerFinishedWork]->getFinishTime());

    data_.sourcesData[application->getSourceIndex()].handlingTime += timeInHandler;
    data_.sourcesData[application->getSourceIndex()].bufferingTime += (handlers_[handlerFinishedWork]->getFinishTime() - application->getTimeOfCreation());
    data_.handlersData[nextHandlerIndex].workingTime += timeInHandler;

  } else {
    // TODO Для учета статистики (время работы в приборе)
    const int earliestSourceIndex = getEarliestSourceIndex();
    application = std::make_shared<Application>(earliestSourceIndex, sources_[earliestSourceIndex]->getPostTime());

    buffer_->addApplication(application);
    application = buffer_->removeApplication();

    const int nextHandlerIndex = getNextHandler(application->getTimeOfCreation());
    const double timeInHandler = handlers_[nextHandlerIndex]->handleApplication(application->getTimeOfCreation());

    data_.sourcesData[application->getSourceIndex()].bufferingTime += 0;
    data_.sourcesData[application->getSourceIndex()].handlingTime += timeInHandler;
    data_.handlersData[nextHandlerIndex].workingTime += timeInHandler;

    sources_[earliestSourceIndex]->postApplication();
    data_.sourcesData[earliestSourceIndex].generatedAppsCount++;
  }

  data_.sourcesData[application->getSourceIndex()].acceptedAppsCount++;
}

int FunctionalModule::getNextHandler(const double &timeNow) {
  for (size_t i = handlerPointer_; i < handlers_.size(); i++) {
    if (!handlers_[i]->isWorking(timeNow)) {
      if (i == handlers_.size()) {
        handlerPointer_ = 0;
      } else {
        handlerPointer_ = i + 1;
      }
      return static_cast<int>(i);
    }
  }

  for (size_t i = 0; i < handlerPointer_; i++) {
    if (!handlers_[i]->isWorking(timeNow)) {
      if (i == handlers_.size()) {
        handlerPointer_ = 0;
      } else {
        handlerPointer_ = i + 1;
      }
      return static_cast<int>(i);
    }
  }

  return -1;
}

FunctionalModule::FunctionalModule(std::vector<std::shared_ptr<Source>> sources,
                                   std::shared_ptr<Buffer> buffer,
                                   std::vector<std::shared_ptr<Handler>> handlers):
  sources_(sources),
  buffer_(buffer),
  handlers_(handlers),
  handlerPointer_(0),
  data_(sources.size(), handlers.size())
{
  cleanUp();
}

void FunctionalModule::simulate(const size_t &steps) {
  cleanUp();
  postFirstApplications();
  for (int i = 0; i < steps; ++i) {
    simulationStep();
  }
}

void FunctionalModule::simulationStep() {
  std::pair<bool, int> earliestEvent = getEarliestEvent();

  if (earliestEvent.first) {
    data_.timeNow = sources_[earliestEvent.second]->getPostTime();
    handleCreationOfNewApplication(earliestEvent.second);

  } else {
    data_.timeNow = handlers_[earliestEvent.second]->getFinishTime();
    handleEndOfHandlerWork(earliestEvent.second);

  }
}

void FunctionalModule::totalGeneratedAppsSimulation(const size_t &totalApps) {
  cleanUp();
  postFirstApplications();

  while (true) {
    simulationStep();

    size_t apps = 0;
    for (size_t i = 0; i < sources_.size(); ++i) {
      apps += data_.sourcesData[i].generatedAppsCount;
    }

    if (apps >= totalApps) {
      break;
    }
  }
}

