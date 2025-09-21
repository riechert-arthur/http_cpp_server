#ifndef ROUTER_H
#define ROUTER_H

#include "data.hpp"

#include <unordered_map>
#include <string>
#include <functional>

#define POST "POST"
#define GET  "GET"

namespace router {

using handler = std::function<std::string(data::request_t)>;

typedef struct route {
  std::string path;
  std::string method;
  bool operator == (const route& r) const {
    return path == r.path && method == r.method;
  }
} Route;

struct RouteHasher {
  size_t operator()(const Route& r) const {
    return std::hash<std::string>()(r.path) ^ std::hash<std::string>()(r.method) << 1;
  }
};

class Router {
public:
  Router(void);
  void add_route(std::string,std::string,handler);
  std::optional<handler> get_handler(const Route&);
private:
  std::unordered_map<Route,handler, RouteHasher> route_map;
};
}
#endif