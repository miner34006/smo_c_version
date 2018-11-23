//
// Created by Богдан Полянок on 05.10.2018.
//

#include "FunctionalModule.hpp"

void FunctionalModule::cleanUp() {
  for (auto &data : data_) {
    data.cleanUp();
  }
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
    data_[i].generatedAppsCount ++;
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
    application_ptr replacedApplication = buffer_->replaceApplication(application);
    data_[replacedApplication->getSourceIndex()].refusedAppsCount++;
    // TODO учитываем статистику для выброшенной зявки
  }
  sources_[sourceGeneratedApplication]->postApplication();
  data_[sourceGeneratedApplication].generatedAppsCount ++;
  // TODO Учет статистики (среднее число apps в буфере)
}

void FunctionalModule::handleEndOfHandlerWork(const size_t &handlerFinishedWork) {
  application_ptr application;
  if (!buffer_->isEmpty()) {
    // TODO Для учета статистики (время работы в приборе)
    application = buffer_->removeApplication();
    const int nextHandlerIndex = getNextHandler(handlers_[handlerFinishedWork]->getFinishTime());
    const double timeInHandler = handlers_[nextHandlerIndex]->handleApplication(handlers_[handlerFinishedWork]->getFinishTime());
  } else {
    // TODO Для учета статистики (время работы в приборе)
    const int earliestSourceIndex = getEarliestSourceIndex();
    application = std::make_shared<Application>(earliestSourceIndex, sources_[earliestSourceIndex]->getPostTime());

    buffer_->addApplication(application);
    application = buffer_->removeApplication();

    const int nextHandlerIndex = getNextHandler(application->getTimeOfCreation());
    const double timeInHandler = handlers_[nextHandlerIndex]->handleApplication(application->getTimeOfCreation());

    sources_[earliestSourceIndex]->postApplication();
    data_[earliestSourceIndex].generatedAppsCount++;
  }

  data_[application->getSourceIndex()].acceptedAppsCount++;
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

FunctionalModule::FunctionalModule(source_vector sources,
                                   buffer_ptr buffer,
                                   handlers_vector handlers):
  sources_(sources),
  buffer_(buffer),
  handlers_(handlers),
  handlerPointer_(0),
  data_({})
{
  cleanUp();

  const size_t sourcesCount = sources_.size();
  for (size_t i = 0; i < sourcesCount; ++i) {
    simulationData data;
    data_.push_back(data);
  }
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
    handleCreationOfNewApplication(earliestEvent.second);
  } else {
    handleEndOfHandlerWork(earliestEvent.second);
  }
}

