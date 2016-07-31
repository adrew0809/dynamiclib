#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <iostream>
#include <memory>
#include <string>

class Interface 
{
public:
  Interface() { std::cout << "Interface's ctor\n"; }
  virtual ~Interface() { std::cout << "Interface's dtor\n"; }
  virtual std::string talk() const = 0;

  virtual std::unique_ptr<Interface> clone() const = 0;

  static constexpr const char* const createFunctionName() 
  {
    return "createInterface";
  }

  static constexpr const char* const destroyFunctionName() 
  {
    return "destroyInterface";
  }
};

extern "C" {
  Interface* createInterface();
  void destroyInterface(Interface*);
}

#endif
