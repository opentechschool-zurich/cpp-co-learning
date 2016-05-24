CXXFLAGS += -I.
#CXXFLAGS += -std=c++14
#make this work for gcc 4.8.4
CXXFLAGS += -std=c++1y
CXXFLAGS += -Wall -Wextra -Werror
#CXXFLAGS += -fsanitize=undefined -fno-sanitize-recover=undefined
CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer

GTEST_LIBS = -lgtest -lgmock -lgmock_main -pthread
GTEST_LIBDIR =

HPP_FILES = $(wildcard *.hpp)
CPP_FILES = $(wildcard *.cpp)

.PHONY: test.output
test.output: test makefile
	@./$< --gtest_shuffle

test: makefile $(CPP_FILES)
	@$(CXX) $(CXXFLAGS) -O $(CPP_FILES) $(GTEST_LIBS) /richi/Src/cpp-co-learning/programming-principles-and-practice/26-testing/Richard/testproject/build/googletest-build/googlemock/gtest/libgtest.a /richi/Src/cpp-co-learning/programming-principles-and-practice/26-testing/Richard/testproject/build/googletest-build/googlemock/gtest/libgtest_main.a /richi/Src/cpp-co-learning/programming-principles-and-practice/26-testing/Richard/testproject/build/googletest-build/googlemock/libgmock.a /richi/Src/cpp-co-learning/programming-principles-and-practice/26-testing/Richard/testproject/build/googletest-build/googlemock/libgmock_main.a -I /richi/Src/cpp-co-learning/programming-principles-and-practice/26-testing/Richard/testproject/build/googletest-src/googlemock/include/ -o $@
