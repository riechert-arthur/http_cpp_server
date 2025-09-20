CXX      := c++
CXXFLAGS := -std=c++20 -Iinclude -Wall -Wextra -pedantic

SRC      := server.cpp app.cpp utils.cpp router.cpp
TARGET   := run.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(TARGET)