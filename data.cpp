#include "data.hpp"
#include "utils.hpp"

#include <format>
#include <regex>
#include <iostream>

data::request_t data::parse_request(const char *buf, ssize_t bytes_rcvd) {
  std::regex r1(SEPARATE_BODY), r2(REQUEST_LINE);
  std::smatch m1, m2;

  std::string req_str(buf, bytes_rcvd);

  if (!std::regex_match(req_str, m1, r1)) {
    return nullptr;
  }

  std::string headers = m1[1].str();
  std::string body = m1[2].str();

  if (!std::regex_search(headers, m2, r2)) {
    return nullptr;
  }

  json j = body.empty() ? json::object() : json::parse(body, nullptr, false);
  if (j.is_discarded()) j = json::object();

  return std::make_unique<data::Request>(m2[1].str(), m2[2].str(), std::move(j));
}

std::string data::response_to_string(const data::Response& r) {
  const std::string& body = r.msg;
  return std::format(
    "HTTP/1.1 {} {}\r\n"
    "Content-Type: application/json\r\n"
    "Access-Control-Allow-Origin: http://localhost:5173\r\n"
    "Content-Length: {}\r\n"
    "Connection: close\r\n"
    "\r\n"
    "{}",
    r.code, r.status, body.size(), body
  );
}