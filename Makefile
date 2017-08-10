CXXFLAGS += -std=c++11

all:
	$(MAKE) -C test
	$(MAKE) -C latex

clean:
	$(MAKE) clean -C test
	$(MAKE) clean -C latex
