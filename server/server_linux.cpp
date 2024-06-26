#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <csignal>
#include <cstring>

volatile bool running = true;

void signal_handler(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        std::cout << "Stopping server..." << std::endl;
        running = false;
    }
}

int main(int argc, char* argv[]) {
    // Create a socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Bind the socket to an address and port
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(server_fd);
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) == -1) {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(server_fd);
        return 1;
    }

    // Set up signal handlers for SIGINT and SIGTERM
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    std::cout << "Server listening on port 8080" << std::endl;

    while (running) {
        // Accept an incoming connection
        sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_addr_len);
        if (client_fd == -1) {
            std::cerr << "Failed to accept connection" << std::endl;
            continue;
        }

        // Read the request
        char buffer[1024];
        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read == -1) {
            std::cerr << "Failed to read from socket" << std::endl;
            close(client_fd);
            continue;
        }
        buffer[bytes_read] = '\0';

        // Send a response
        std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!";
        ssize_t bytes_written = write(client_fd, response.c_str(), response.length());
        if (bytes_written == -1) {
            std::cerr << "Failed to write to socket" << std::endl;
        }

        // Close the connection
        close(client_fd);
    }

    // Cleanup
    close(server_fd);
    std::cout << "Server stopped" << std::endl;
    return 0;
}
