#pragma once

#include <random>
#include <memory>
#include <string>


class GENERATEPASSWORD {
public:
    GENERATEPASSWORD();

    static std::unique_ptr<std::string> get_password(const int &length);
};
