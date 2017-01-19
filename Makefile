GTEST_DIR = $(GTEST_ROOT)

USER_DIR = code
TEST_DIR = test

CXXFLAGS += -g -Wall -Wextra
CPPFLAGS_TEST = $(CPPFLAGS) -isystem $(GTEST_DIR)/include
CXXFLAGS_TEST = $(CXXFLAGS) -pthread

TESTS = $(TEST_DIR)/sample

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# house-keeping build targets.
all : $(TESTS)

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS_TEST) -I$(GTEST_DIR) $(CXXFLAGS_TEST) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS_TEST) -I$(GTEST_DIR) $(CXXFLAGS_TEST) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# generic rules
$(USER_DIR)/%.o : $(USER_DIR)/%.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS_TEST) $(CXXFLAGS_TEST) -c $< -o $@

$(TEST_DIR)/%.o : $(TEST_DIR)/%.cpp $(USER_DIR)/%.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS_TEST) $(CXXFLAGS_TEST) -c $< -o $@

$(TEST_DIR)/% : $(TEST_DIR)/%.o gtest_main.a
	$(CXX) $(CPPFLAGS_TEST) $(CXXFLAGS_TEST) -lpthread $^ -o $@

$(USER_DIR)/% : $(USER_DIR)/%.cpp %(GTEST_HEADERS)
	$(CXX) $(CXXFLAGS) $< -o $@
