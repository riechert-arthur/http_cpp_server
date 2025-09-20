#include "app.hpp"
using namespace std;

#define LOCALHOST    "127.0.0.1"
#define PORT         3000

int main() {
  app::HttpServer myapp(LOCALHOST, static_cast<uint16_t>(PORT));
  router::Router myrouter;

  myrouter.add_route("/api", []() {
    return std::string{
      R"(HTTP/1.1 200 OK
      Content-Type: text/plain
      Content-Length: 12
      Connection: close

      Hello World
    )"};
  });

  myrouter.add_route("/auth", []() {
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