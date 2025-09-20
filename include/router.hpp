#ifndef ROUTER_H
#define ROUTER_H

#include <unordered_map>
#include <string>
#include <functional>

namespace router {

using handler = std::function<std::string()>;

class Router {
public:
  Router(void);
  void add_route(std::string,handler);
  std::optional<handler> get_handler(std::string);
private:
  std::unordered_map<std::string,handler> route_map;
};
}
#endif