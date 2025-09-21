#include "app.hpp"
#include "utils.hpp"
#include "data.hpp"

struct FdCloser {
  int& fd;
  ~FdCloser() noexcept { if (fd >= 0) ::close(fd); }
};

app::HttpServer::HttpServer(std::string addr, std::uint16_t port)
  : addr(std::move(addr)), port(port) {};

void app::HttpServer::add_router(router::Router router) {
  this->router = std::move(router);
}

void app::HttpServer::run() {
  in_addr_t my_addr = parse_str_ipv4(addr);

  try {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    FdCloser guard{ s };

    if (s == -1) {
      throw std::runtime_error("Error opening a new socket.");
    }

    struct sockaddr_in saddr {};
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = my_addr;
    saddr.sin_port = htons(port);

    #ifdef __APPLE__
    saddr.sin_len = sizeof(saddr);
    #endif
    
    if (::bind(s, reinterpret_cast<const struct sockaddr*>(&saddr), sizeof(struct sockaddr_in)) == -1) {
      throw std::runtime_error(
        std::format("Error binding socket to port {}", port)
      );
    }

    int enabled = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enabled, sizeof(int)) == -1) {
      throw std::runtime_error("Error setting socket to reuse.");
    }

    
    if (listen(s, BUFFER_SIZE) == -1) {
      throw std::runtime_error("Error starting listen.");
    }

    struct sockaddr_in peer_saddr {};
    char buf[BUFFER_SIZE];
    ssize_t bytes_rcvd;

    std::cout << std::format("Server started at {}:{}...", addr, port) << std::endl;

    while (true) {

      socklen_t paddr_len = sizeof(peer_saddr);
      int ps = accept(s, reinterpret_cast<struct sockaddr*>(&peer_saddr), &paddr_len);

      if (ps == -1) {
        if (errno == EINTR) continue;
        throw std::runtime_error(
          std::format("Error accepting connection: {}", std::strerror(errno))
        );
      }
      FdCloser c_guard { ps };

      if ((bytes_rcvd = read(ps, &buf, sizeof(buf))) == -1) {
        throw std::runtime_error(
          std::format("Error reading from connection: {}", std::strerror(errno))
        );
      } else if (bytes_rcvd == 0) {
        throw std::runtime_error("Socket closed successfully!");
      }

      data::request_t req = data::parse_request(buf, bytes_rcvd);

      auto h = this->router.get_handler(req->route);
      std::string res;
      if (h) {
        res = (*h)(std::move(req));
      }

      if (::send(ps, res.data(), res.size(), 0) == -1) {
        throw std::runtime_error("Error while ponging peer!");
      }
    }
  } catch(const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}