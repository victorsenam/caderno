CXXFLAGS += -std=c++11

all:
	$(MAKE) -C test

clean:
	$(MAKE) clean -C test
