#include "app.hpp"
using namespace std;

#define LOCALHOST    "127.0.0.1"
#define PORT         3000

int main() {
  app::HttpServer myapp(LOCALHOST, static_cast<uint16_t>(PORT));
  router::Router myrouter;

  myrouter.add_route("/api", POST, [](data::request_t req) {
    return data::Response {
      STATUS_OK,
      SUCCESS_CODE,
      req->body.dump()
    };
  });

  myrouter.add_route("/api", GET, [](data::request_t req) {
    return data::Response {
      STATUS_OK,
      SUCCESS_CODE,
      std::format("Echoing:\n\n{}\n", req->body.dump())
    };
  });

  myapp.add_router(std::move(myrouter));
  myapp.run();
}