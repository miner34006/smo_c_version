#include <iostream>
#include <vector>

#include "headers/Source.hpp"
#include "headers/Handler.hpp"
#include "headers/Buffer.hpp"
#include "headers/FunctionalModule.hpp"
#include "headers/RingSelection.hpp"
#include "headers/FreeAddition.hpp"


int main() {
  std::srand(unsigned(std::time(nullptr)));

  std::shared_ptr<TimeBehaviour> exponentialTimeGenerator = std::make_shared<ExponentialTimeBehavior>();

  const double a = 1;
  const double b = 3;
  std::shared_ptr<TimeBehaviour> infiniteUniformTimeGenerator = std::make_shared<InfiniteUniformTimeBehavior>(a, b);

  double intensity = 3.0;
  std::vector<std::shared_ptr<Source>> sources = {
    std::make_shared<Source>(intensity, exponentialTimeGenerator),
    std::make_shared<Source>(intensity, exponentialTimeGenerator),
    std::make_shared<Source>(intensity, exponentialTimeGenerator),
  };

  intensity = 8;
  std::vector<std::shared_ptr<Handler>> handlers = {
    std::make_shared<Handler>(0, infiniteUniformTimeGenerator),
    std::make_shared<Handler>(0, infiniteUniformTimeGenerator),
  };

  const size_t bufferSize = 5;
  std::shared_ptr<SelectionStrategy> selectionStrategy = std::make_shared<RingSelection>();
  std::shared_ptr<AdditionStrategy> additionStrategy = std::make_shared<FreeAddition>();
  std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>(selectionStrategy, additionStrategy, bufferSize);

  FunctionalModule functionalModule(sources, buffer, handlers);
  functionalModule.simulate(999999);

  for (size_t i = 0; i < sources.size(); ++i) {
    std::cout << "Stats for " << i << " source:\n";
    std::cout << "\t generatedAppsCount = " << functionalModule.data_.sourcesData[i].generatedAppsCount << '\n';
    std::cout << "\t refusedAppsCount = " << functionalModule.data_.sourcesData[i].refusedAppsCount << '\n';
    std::cout << "\t acceptedAppsCount = " << functionalModule.data_.sourcesData[i].acceptedAppsCount << '\n';
    std::cout << "\t getProbabilityOfFailure = " << functionalModule.data_.getProbabilityOfFailure(i) << '\n';
    std::cout << "\t averageTimeInSystem = " << functionalModule.data_.getAverageTimeInSystem(i) << '\n';
    std::cout << "\t averageHandlingTime = " << functionalModule.data_.getAverageHandlingTime(i) << '\n';
    std::cout << "\t averageBufferingTime = " << functionalModule.data_.getAverageBufferingTime(i) << '\n';

    std::cout << '\n';
  }

  for (size_t i = 0; i < handlers.size(); ++i) {
    std::cout << "Stats for " << i << " handler:\n";
    std::cout << "\t getEmploymentRate = " << functionalModule.data_.getEmploymentRate(i) << '\n';
  }

  return 0;
}