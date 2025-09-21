#ifndef DATA_HPP
#define DATA_HPP

#include "external/json.hpp"

#include <string>
#include <memory>
#include <sys/types.h>

using json = nlohmann::json;

#define REQUEST_LINE  R"((GET|POST|PATCH|DELETE|OPTIONS)\s+(\S+)\s+HTTP/1\.[01])"
#define SEPARATE_BODY R"(^([\s\S]*?)\r\n\r\n([\s\S]*)$)"

namespace data {

typedef struct request {
  std::string method;
  std::string path;
  json body;
} Request;

using request_t = std::unique_ptr<data::Request>;

typedef struct response {
  std::string status;
  std::uint16_t code;
  std::string msg;
} Response;

request_t parse_request(const char*, ssize_t);
std::string response_to_string(const data::Response&);

}

#endif