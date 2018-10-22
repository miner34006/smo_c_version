//
// Created by Богдан Полянок on 05.10.2018.
//

#include "../headers/FunctionalModule.hpp"

void FunctionalModule::cleanUp() {
  buffer_->cleanUp();
  for (auto &source : sources_) {
    source->cleanUp();
  }
  for (auto &handler : handlers_) {
    handler->cleanUp();
  }

  handlerPointer = 0;
}

void FunctionalModule::postFirstApplications() {
  for (auto &source : sources_) {
    source->postApplication();
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

//  const int earliestHandlerIndex = getEarliestHandlerIndex();
//  const double handlerTime = handlers_[earliestHandlerIndex]->getFinishTime();
  const int nextHandlerIndex = getNextHandler();
  if (nextHandlerIndex == -1) {
    return {true, earliestSourceIndex};
  }

  if (sourceTime < handlers_[nextHandlerIndex]->getFinishTime()) {
    return {true, earliestSourceIndex};
  } else {
    return {false, nextHandlerIndex};
  }
}

void FunctionalModule::doIteration() {
  std::pair<bool, int> earliestEvent = getEarliestEvent();

  if (earliestEvent.first) {
    handleCreationOfNewApplication(earliestEvent.second);
  } else {
    handleEndOfHandlerWork(earliestEvent.second);
  }
}

void FunctionalModule::handleEndOfHandlerWork(const size_t &handlerFinishedWork) {
  if (!buffer_->isEmpty()) {
    std::shared_ptr<Application> application = buffer_->removeApplication();
    // Подсчитываем статистику для app
  } else {
    // Берем первую заявку от источника
  }
}

int FunctionalModule::getNextHandler(const double &timeNow) {
  for (size_t i = handlerPointer; i < handlers_.size(); i++) {
    if (!handlers_[i]->isWorking(timeNow)) {
      if (i == handlers_.size()) {
        handlerPointer = 0;
      } else {
        handlerPointer = i + 1;
      }
      return static_cast<int>(i);
    }
  }

  for (size_t i = 0; i < handlerPointer; i++) {
    if (!handlers_[i]->isWorking(timeNow)) {
      if (i == handlers_.size()) {
        handlerPointer = 0;
      } else {
        handlerPointer = i + 1;
      }
      return static_cast<int>(i);
    }
  }

  return -1;
}

void FunctionalModule::handleCreationOfNewApplication(const size_t &sourceGeneratedApplication) {
  auto application = std::make_shared<Application>(sourceGeneratedApplication, sources_[sourceGeneratedApplication]->getPostTime());

  const bool hasAdded = buffer_->addApplication(application);
  if (!hasAdded) {
    // Не добавили заявку в буфер -> заменяем заявку
    std::shared_ptr<Application> replacedApplication = buffer_->replaceApplication(application);
    // учитываем статистику
  }
  sources_[sourceGeneratedApplication]->postApplication();

  // Учет статистики (среднее число apps в буфере)
}




