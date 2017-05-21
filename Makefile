CODE_NAMES = /math/fft /geometry
TEST_NAMES = /math/fft /geometry_vec_ll /geometry_vec_dbl

# based on https://github.com/google/googletest/blob/master/googletest/make/Makefile
GTEST_DIR = $(GTEST_ROOT)

CODE_DIR = code
TEST_DIR = test

CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++11 -Wno-sign-compare

TESTS = $(addprefix $(TEST_DIR),$(TEST_NAMES))
CODES = $(addsuffix .cpp,$(addprefix $(CODE_DIR),$(CODE_NAMES)))
TEST_OBJECTS = $(addsuffix .o,$(TESTS))

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

.PHONY: all clean

# house-keeping build targets.
all : $(TESTS) $(TEST_DIR)/main

clean :
	rm -f $(TESTS) $(TEST_OBJECTS) 

# gtest rules
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# main target rule
$(TEST_DIR)/main.o : $(TEST_DIR)/main.cpp $(TESTS) $(TEST_OBJECTS) $(CODES) $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TEST_DIR)/main : $(TEST_DIR)/main.o $(TESTS) $(TEST_OBJECTS) $(CODES) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $(TEST_DIR)/main.o $(TEST_OBJECTS) gtest_main.a -o $@

# test rules
$(TEST_DIR)/math/fft.o : $(TEST_DIR)/math/fft.cpp $(CODE_DIR)/math/fft.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TEST_DIR)/geometry_vec_ll.o : $(TEST_DIR)/geometry_vec_ll.cpp $(CODE_DIR)/geometry.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TEST_DIR)/geometry_vec_dbl.o : $(TEST_DIR)/geometry_vec_dbl.cpp $(CODE_DIR)/geometry.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# generic rules
$(TESTS) : $(TEST_DIR)/% : $(TEST_DIR)/%.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
