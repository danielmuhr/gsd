// main.cpp

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <thread>

using namespace web;
using namespace http;
using namespace http::experimental::listener;

class UserService
{
public:
    UserService() : listener("http://localhost:8080/users")
    {
        listener.support(methods::POST, std::bind(&UserService::handle_post, this, std::placeholders::_1));
        listener.support(methods::GET, std::bind(&UserService::handle_get, this, std::placeholders::_1));
    }

    void open() { listener.open().wait(); }
    void close() { listener.close().wait(); }

private:
    void handle_post(http_request request)
    {
        // Parse the JSON request body
        request.extract_json().then([=](json::value body) {
            // Assuming the JSON contains 'name' and 'email' fields
            std::string name = body[U("name")].as_string();
            std::string email = body[U("email")].as_string();

            // Here, you can add the logic to save the user data to a database or perform any other actions.

            json::value response;
            response[U("status")] = json::value::string(U("User registered successfully"));

            // Send the response
            request.reply(status_codes::OK, response);
        }).wait();
    }

    void handle_get(http_request request)
    {
        // Assuming that the user_id is passed as a query parameter, e.g., /users?id=123
        std::string user_id = utility::conversions::to_utf8string(request.absolute_uri().query());

        // Here, you can add the logic to fetch user data from the database based on the user_id.

        json::value response;
        response[U("name")] = json::value::string(U("John Doe"));
        response[U("email")] = json::value::string(U("john.doe@example.com"));

        // Send the response
        request.reply(status_codes::OK, response);
    }

    http_listener listener;
};


int main()
{
    try
    {
        UserService user_service;
        user_service.open();

        std::cout << "User Service is listening..." << std::endl;
        std::this_thread::sleep_for(std::chrono::minutes(10)); // Keep the service running for some time

        user_service.close();
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}