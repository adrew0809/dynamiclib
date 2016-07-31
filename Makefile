CXXFLAGS := -std=c++11

.PHONY : all clean

all : main interface_a.so interface_b.so

main : main.o 
	$(CXX) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS)

interface_a.so : a.o

interface_b.so : b.o

b.o : b.cpp b.h Interface.h

a.o : a.cpp a.h Interface.h

main.o : main.cpp Interface.h DL.h

%.so :
	$(CXX) -dynamiclib -flat_namespace -o $@ $^

%.o : 
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

clean :
	rm -f interface_a.so
	rm -f a.o
	rm -f interface_b.so
	rm -f b.o
	rm -f main
	rm -f main.o

