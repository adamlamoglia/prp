.PHONY: all clean fence debug

CPPSOURCES = $(shell find . -name '*.cpp')
CPPFLAGS = -std=c++11 -O3

all: prp clean
fence: fnc clean
debug: dbg clean

prp: $(CPPSOURCES:.cpp=.o)
	@g++ $(CPPFLAGS) -o $@ $^

dbg: CPPFLAGS += -g -p -pg -Wall
dbg: $(CPPSOURCES:.cpp=.o)
	@g++ $(CPPFLAGS) -o debug $^

fnc: CPPFLAGS += -lfence
fnc: $(CPPSOURCES:.cpp=.o)
	@g++ $(CPPFLAGS) -o fence $^

%.o: %.cpp %.h
	@g++ -c $(CPPFLAGS) $< -o $@

%.o: %.cpp
	@g++ -c $(CPPFLAGS) $< -o $@

-include $(CPPSOURCES:.cpp=.d)

%.d: %.cpp
	@g++ $(CPPFLAGS) $< -MM -MD

clean:
	@-rm -f */*.o *.o */*.d *.d */*~
