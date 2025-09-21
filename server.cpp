#include "app.hpp"
using namespace std;

#define LOCALHOST    "127.0.0.1"
#define PORT         3000

int main() {
  app::HttpServer myapp(LOCALHOST, static_cast<uint16_t>(PORT));
  router::Router myrouter;

  myrouter.add_route("/api", [](data::request_t req) {
    data::Response res;
    res.status = STATUS_OK;
    res.code = SUCCESS_CODE;
    res.msg = std::format("This is a response from {} for {}\n", req->route, req->method);
    
    return data::response_to_string(&res);
  });

  myrouter.add_route("/auth", [](data::request_t req) {
    return std::string{
      R"(HTTP/1.1 200 OK
      Content-Type: text/plain
      Content-Length: 12
      Connection: close

      We got a router!
    )"};
  });

  myapp.add_router(myrouter);
  myapp.run();
}