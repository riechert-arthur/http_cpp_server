#include "router.hpp"

using namespace router;

Router::Router() {};

void Router::add_route(std::string path, std::string method, handler func) {
  Route r { path, method };
  route_map[r] = func;
}

std::optional<handler> Router::get_handler(const Route& r) {
  handler h = route_map[r];
  return h ? std::optional<handler>(std::move(h)) : std::nullopt;
}