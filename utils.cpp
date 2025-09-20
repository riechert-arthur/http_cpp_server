#include "utils.hpp"

in_addr_t parse_str_ipv4(const std::string& str_addr) {

  std::regex re(IPV4_DELIMITER);
  std::sregex_token_iterator it(str_addr.begin(), str_addr.end(), re, -1), end;

  in_addr_t res = 0;
  for (int i = 0; i < 4; ++i, ++it)
    res = (res << 8) | static_cast<in_addr_t>(std::atoi(it->str().c_str()));

  return htonl(res);
}