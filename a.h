#ifndef A_H_
#define A_H_

#include "Interface.h"

class A : public Interface
{
public:
  A();
  ~A() override;
  std::string talk() const override;
  std::unique_ptr<Interface> clone() const override;
};

#endif
