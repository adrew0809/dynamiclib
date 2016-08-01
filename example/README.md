# Example use of DynamicLib

DynamicLib provides a convenient way to interface with polymorphic classes
contained in shared objects. The shared object library can then by changed
without requiring recompilation to achieve different results at runtime.

In this example, `Interface` is a pure virtual base class.
`A` and `B` are concrete implementations of `Interface`.
`Interface.h` also declares  `extern "C"` functions 
for creating and destroying `Inteface` objects.
`a.h` and `b.h` each implement these functions to return
a smart pointer to an `A` or a `B`, respectively.

`main.cpp` only knows about `Interface.h`. It loads the dynamic
library `interface.so` and creates an `Interface` object.
Depending on whether `interface.so` is `interface_a.so` or
`interface_b.so`, `main` will get either an `A` or a `B`.
Then, polymorphic calls to the `Interface` object will
use either the `A` or the `B` implementation.

Example run:

 cd example
 make
 ln -s interface_a.so interface.so
 ./main
 Starting program...
 Dl ctor
 Interface's ctor
 A's ctor
 obj says "I'm an A!"
 Interface's ctor
 A's ctor
 clone says "I'm an A!"
 A's dtor
 Interface's dtor
 A's dtor
 Interface's dtor
 Dl dtor

