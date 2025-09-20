#ifndef APP_HPP
#define APP_HPP

#include <string>
#include <iostream>
#include <format>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "router.hpp"

#define BUFFER_SIZE  1024

namespace app{

class HttpServer {
public:
  HttpServer(std::string addr, std::uint16_t port);  
  void add_router(router::Router);
  void run(void);
private:
  std::string addr;
  std::uint16_t port;
  router::Router router;
};
}

#endif