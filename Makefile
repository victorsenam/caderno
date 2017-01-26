# based on https://github.com/google/googletest/blob/master/googletest/make/Makefile
GTEST_DIR = $(GTEST_ROOT)

USER_DIR = code
TEST_DIR = test

CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++11

NAMES = /geometry/inte /geometry/vect /sample
TESTS = $(addprefix $(TEST_DIR),$(NAMES))
CODES = $(addsuffix .cpp,$(addprefix $(USER_DIR),$(NAMES)))
TESTS_OBJECTS = $(addsuffix .o,$(TESTS))

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

.PHONY: all clean

# house-keeping build targets.
all : $(TESTS)

clean :
	rm -f $(TESTS) $(TESTS_OBJECTS) $(TEST_DIR)/main $(TEST_DIR)/main.o gtest.a gtest_main.a *.o

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
$(TEST_DIR)/main.o : $(TEST_DIR)/main.cpp $(TESTS) $(TESTS_OBJECTS) $(CODES) $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TEST_DIR)/main : $(TEST_DIR)/main.o $(TESTS) $(TESTS_OBJECTS) $(CODES) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $(TEST_DIR)/main.o $(TESTS_OBJECTS) gtest_main.a -o $@

# generic rules
$(TESTS_OBJECTS) : $(TEST_DIR)/%.o : $(TEST_DIR)/%.cpp $(USER_DIR)/%.cpp $(USER_DIR)/header.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TESTS) : $(TEST_DIR)/% : $(TEST_DIR)/%.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
