#pragma once

#include <string>

struct ProgramOptions {
    std::string input_image;
    std::string output_image;
    std::string password;
    bool password_generate = false;
    std::string password_from;
};
