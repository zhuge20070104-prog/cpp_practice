#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  int count = 1;
  std::string name;
  while(count < argc) {
    name += argv[count++];
  }

  name.erase(0, name.find_first_not_of(" \t\r\n\f\v"));
  name.erase(name.find_last_not_of(" \t\r\n\f\v") + 1);
  std::cout << name << std::endl;
  return EXIT_SUCCESS;
}