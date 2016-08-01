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

    $cd example
    $make
    c++ -std=c++11 -I../include -c -o main.o main.cpp
    c++  -o main main.o  
    c++ -std=c++11  -c -o a.o a.cpp
    c++ -dynamiclib -flat_namespace -o interface_a.so a.o
    c++ -std=c++11  -c -o b.o b.cpp
    c++ -dynamiclib -flat_namespace -o interface_b.so b.o
    $ln -s interface_a.so interface.so
    $./main
    Starting program...
    A's ctor
    obj says "I'm an A!"
    A's ctor
    clone says "I'm an A!"
    A's dtor
    A's dtor
    $ln -sf interface_b.so interface.so 
    $./main 
    Starting program...
    B's ctor
    obj says "I'm an B :)"
    B's ctor
    clone says "I'm an B :)"
    B's dtor
    B's dtor

