#include "headers/password_generator.h"
#include "spdlog/spdlog.h"


std::unique_ptr<std::string> GENERATEPASSWORD::get_password(const int &length) {
    std::random_device rd;
    std::random_device::result_type SEED = rd();
    std::mt19937 generator = std::mt19937(SEED);

    std::unique_ptr<std::string> password = std::make_unique<std::string>("");

    for (int i = 0; i < length; ++i) {
        std::uniform_int_distribution<> distribution(0, 255);
        password->push_back((char)distribution(generator));
    }

    spdlog::debug("Successfully generated password (symbols: {})", length);
    return password;
}
