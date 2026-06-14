#include "bootstrap/bootstrap.hpp"

#include <exception>
#include <iostream>

int main() {
    try {
        Bootstrap bootstrap;
        auto api = bootstrap.createChannelApi();

        api.setChannel(15);

        const auto message = api.getChannelMessage();

        std::cout << message << "\n";

        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "fatal_error: " << ex.what() << "\n";
        return 1;
    }
}
