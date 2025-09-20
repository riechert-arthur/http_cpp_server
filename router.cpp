#include "router.hpp"

using namespace router;

Router::Router() {};

void Router::add_route(std::string path, handler func) {
  route_map[path] = func;
}

std::optional<handler> Router::get_handler(std::string path) {
  handler h = route_map[path];
  return h ? std::optional<handler>(std::move(h)) : std::nullopt;
}