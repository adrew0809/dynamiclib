#ifndef B_H_
#define B_H_

#include "Interface.h"

class B : public Interface
{
public:
  B();
  ~B() override;
  std::string talk() const override;
  std::unique_ptr<Interface> clone() const override;
};

#endif
