// main.cpp
#include <iostream>
#include <string>
#include <cpr/cpr.h>

int main() {
    std::string serviceAResponse = cpr::Get(cpr::Url{"http://service-a:8080/data"}).text;
    std::string serviceBResponse = cpr::Get(cpr::Url{"http://service-b:8081/process"}, cpr::Payload{{"data", serviceAResponse}}).text;

    std::cout << "Result: " << serviceBResponse << std::endl;

    return 0;
}

