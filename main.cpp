#include <iostream>
#include <vector>

int main() {

  std::vector<std::shared_ptr<int*>> myVector;
  myVector.resize(2);

  std::cout << myVector.size();

  return 0;
}