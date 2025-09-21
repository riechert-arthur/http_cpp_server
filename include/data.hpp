#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <memory>
#include <sys/types.h>

namespace data {

typedef struct request {
  std::string method;
  std::string route;
} Request;

using request_t = std::unique_ptr<data::Request>;

typedef struct response {
  std::string status;
  std::uint16_t code;
  std::string msg;
} Response;

request_t parse_request(const char*, ssize_t);
std::string response_to_string(Response*);

}

#endif