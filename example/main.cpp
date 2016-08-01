#include "DynamicLib.h"
#include "Interface.h"


int main(int argc, const char* argv[])
{
  using std::cout;
  cout << "Starting program...\n";
  try {
    const auto dl = DynamicLib("interface.so");
    const auto obj = dl.create<Interface>(Interface::createFunctionName(), Interface::destroyFunctionName());
    cout << "obj says " << obj->talk() << "\n";
    const auto clone = obj->clone();
    cout << "clone says " << clone->talk() << "\n";
  } catch (const std::runtime_error& e) {
    cout << e.what() << "\n";
    return 1;
  }
  return 0;
}
