#include "data.hpp"
#include "utils.hpp"

#include <format>
#include <regex>
#include <iostream>

data::request_t data::parse_request(const char *buf, ssize_t bytes_rcvd) {
  std::regex r(REQUEST_LINE);
  std::smatch m;

  std::string msg(buf, bytes_rcvd);
  if (!std::regex_search(msg, m , r)) {
    return nullptr;
  }

  return std::make_unique<data::Request>(m[1].str(), m[2].str());
}

std::string data::response_to_string(Response* r) {
  return std::format(
    R"(HTTP/1.1 {} {}
    Content-Type: text/plain
    Content-Length: 12
    Connection: close

    {}
  )", r->code, r->status, r->msg);
}