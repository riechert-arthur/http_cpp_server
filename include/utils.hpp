#ifndef UTILS_HPP
#define UTILS_HPP

#include <netinet/in.h>
#include <string>
#include <regex>

#define IPV4_DELIMITER R"(\.)"

in_addr_t parse_str_ipv4(const std::string&);
#endif