#pragma once

#include <memory>
#include <fstream>
#include <iostream>
#include <string>

class GETPASSWORD {
public:
    GETPASSWORD();
    static std::unique_ptr<std::string> from_file(const std::string &path);
    static bool save_password(std::unique_ptr<std::string> &password);
};
