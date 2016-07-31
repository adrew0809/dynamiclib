#include "B.h"

#include <iostream>

B::B()
{
  std::cout << "B's ctor\n";
}

B::~B()
{
  std::cout << "B's dtor\n";
}

std::string B::talk() const
{
  return "\"I'm an B :)\"";
}

std::unique_ptr<Interface> B::clone() const
{
  return std::unique_ptr<B>(new B());
}

extern "C" Interface* createInterface()
{
  return new B();
}

extern "C" void destroyInterface(Interface* ptr)
{
  delete ptr;
}
