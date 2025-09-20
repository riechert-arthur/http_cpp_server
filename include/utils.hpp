#ifndef UTILS_HPP
#define UTILS_HPP

#include <netinet/in.h>
#include <string>
#include <regex>

#define IPV4_DELIMITER R"(\.)"

#define REQUEST_LINE R"((GET|POST|PATCH|DELETE)\s+(\S+)\s+HTTP/1\.[01])"

in_addr_t parse_str_ipv4(const std::string&);
#endif