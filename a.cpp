#include "A.h"

#include <iostream>

A::A()
{
  std::cout << "A's ctor\n";
}

A::~A()
{
  std::cout << "A's dtor\n";
}

std::string A::talk() const
{
  return "\"I'm an A!\"";
}

std::unique_ptr<Interface> A::clone() const
{
  return std::unique_ptr<A>(new A());
}

extern "C" Interface* createInterface()
{
  return new A();
}

extern "C" void destroyInterface(Interface* ptr)
{
  delete ptr;
}
