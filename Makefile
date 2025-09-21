CXX      := c++
CXXFLAGS := -std=c++20 -Iinclude -Wall -Wextra -pedantic

SRC      := server.cpp app.cpp utils.cpp router.cpp data.cpp
TARGET   := run.exe

JSON_HDR := include/external/json.hpp
JSON_URL := https://raw.githubusercontent.com/nlohmann/json/v3.11.3/single_include/nlohmann/json.hpp

all: $(JSON_HDR) $(TARGET)

$(JSON_HDR):
	@mkdir -p $(dir $@)
	curl -L "$(JSON_URL)" -o "$@"

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean distclean
clean:
	rm -f $(TARGET)

distclean: clean
	rm -f $(JSON_HDR)
