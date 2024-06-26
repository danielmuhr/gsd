
// service_a.cpp (Dockerfile: service-a)
#include <iostream>
#include <string>
#include <string>
#include <cpr/cpr.h>

#include <utility>

int main() {
    const std::string data = "Hello, World!";
    const cpr::Url serverUrl{"http://0.0.0.0:8080/data"};
    const cpr::Payload payload{{"data", data}};

    const auto response = cpr::Post(serverUrl, std::move(payload));

    if (response.status_code == 200) {
        std::cout << "Service A: Data sent successfully" << std::endl;
    } else {
        std::cout << "Service A: Failed to send data" << std::endl;
    }

    return response.status_code == 200 ? 0 : 1;
}

// #include <cpr/cpr.h>

// int main(int argc, char **argv) {
//   auto r = cpr::Get(
//       cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
//       cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
//       cpr::Parameters{{"anon", "true"}, {"key", "value"}});
// }