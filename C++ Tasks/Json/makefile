CXX = g++
CXXFLAGS = -std=c++17 -Iinclude
SRCS = src/json_value.cpp src/json_null.cpp src/json_boolean.cpp src/json_number.cpp src/json_string.cpp src/json_array.cpp src/json_object.cpp src/lexer.cpp src/parser.cpp src/json.cpp
OBJS = $(SRCS:.cpp=.o)
MAIN_EXEC = json_main
TEST_EXEC = json_test

all: $(MAIN_EXEC)

$(MAIN_EXEC): $(OBJS) main.cpp
    $(CXX) $(CXXFLAGS) $(OBJS) main.cpp -o $(MAIN_EXEC)

$(TEST_EXEC): $(OBJS) json_test.cpp
    $(CXX) $(CXXFLAGS) $(OBJS) json_test.cpp -o $(TEST_EXEC)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS) $(MAIN_EXEC) $(TEST_EXEC)

test: $(TEST_EXEC)
    ./$(TEST_EXEC)