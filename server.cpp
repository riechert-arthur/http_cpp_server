#include <iostream>
#include <format>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <regex>
using namespace std;

#define LOCALHOST    0x7f000001u
#define PORT         3000
#define BUFFER_SIZE  1024

#define REQUEST_LINE R"((GET|POST|PATCH|DELETE)\s+(\S+)\s+HTTP/1\.[01])"

struct FdCloser {
  int& fd;
  ~FdCloser() noexcept { if (fd >= 0) ::close(fd); }
};

int main() {
  try {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    FdCloser guard{ s };

    if (s == -1) {
      throw std::runtime_error("Error opening a new socket.");
    }

    struct sockaddr_in saddr {};
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(LOCALHOST);
    saddr.sin_port = htons(PORT);

    #ifdef __APPLE__
    saddr.sin_len = sizeof(saddr);
    #endif
    
    if (::bind(s, reinterpret_cast<const struct sockaddr*>(&saddr), sizeof(struct sockaddr_in)) == -1) {
      throw std::runtime_error(
        std::format("Error binding socket to port {}", PORT)
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

    cout << std::format("Listening on {}...", PORT) << endl;

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

      regex r(REQUEST_LINE);
      smatch m;

      string msg(buf, bytes_rcvd);
      if (regex_search(msg, m , r)) {
        std::cout << m[0] << endl;
      }

      const char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 12\r\n"
        "Connection: close\r\n"
        "\r\n"
        "Hello World\n";

      if (::send(ps, response, sizeof(response) - 1, 0) == -1) {
        throw std::runtime_error("Error while ponging peer!");
      }
    }

    return 0;
  } catch(const std::exception& e) {
    std::cerr << "Error: " << e.what() << endl;
    return 1;
  }
}