// service_b.cpp (Dockerfile: service-b)
#include <iostream>
#include <string>
#include <cpr/cpr.h>

int main() {
    cpr::Url serverUrl{"http://0.0.0.0:8081/process"};
    cpr::Response response = cpr::Post(serverUrl, cpr::Payload{});

    if (response.status_code == 200) {
        std::string data = response.text;
        std::cout << "Service B: Received data: " << data << std::endl;
        // Process the data here
    } else {
        std::cout << "Service B: Failed to receive data" << std::endl;
    }

    return 0;
}
