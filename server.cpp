#include "app.hpp"
using namespace std;

#define LOCALHOST    "127.0.0.1"
#define PORT         3000

int main() {
  app::HttpServer myapp(LOCALHOST, static_cast<uint16_t>(PORT));
  myapp.run();
}