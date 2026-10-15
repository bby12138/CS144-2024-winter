#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

#include "socket.hh"

void get_URL(const std::string& host, const std::string& path) {
  TCPSocket socket = TCPSocket();
  Address addr = Address(host, "http");

  // 1. 建立 TCP 连接
  socket.connect(addr);

  // 2. 构造 HTTP 请求
  std::string request = "GET " + path + " HTTP/1.1\r\n" + "Host: " + host +
                        "\r\n" + "Connection: close\r\n" + "\r\n";

  // 3. 完整发送请求
  size_t bytes_send = 0;
  while (bytes_send < request.size()) {
    bytes_send += socket.write(std::string_view(request).substr(bytes_send));
  }
  

  // 4. 读取 HTTP 响应
  while(!socket.eof()) {
    std::string buffer;
    socket.read(buffer);
    std::cout << buffer;
  }

  socket.close();
}

int main(int argc, char* argv[]) {
  try {
    if (argc <= 0) {
      abort();  // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = std::span(argv, argc);

    // The program takes two command-line arguments: the hostname and "path"
    // part of the URL. Print the usage message unless there are these two
    // arguments (plus the program name itself, so arg count = 3 in total).
    if (argc != 3) {
      std::cerr << "Usage: " << args.front() << " HOST PATH\n";
      std::cerr << "\tExample: " << args.front()
                << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const std::string host{args[1]};
    const std::string path{args[2]};

    // Call the student-written function.
    get_URL(host, path);
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
