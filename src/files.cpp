#include "headers/files.h"
#include "spdlog/spdlog.h"

std::unique_ptr<std::string> GETPASSWORD::from_file(const std::string &path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path);
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::unique_ptr<std::string> password = std::make_unique<std::string>();
    password->resize(size);
    file.read(&(*password)[0], size);

    file.close();

    spdlog::debug("Successfully got password from: {}", path);
    return password;
}

bool GETPASSWORD::save_password(std::unique_ptr<std::string> &password) {
    std::ofstream file("password.txt", std::ios::binary);
    if (!file.is_open()) {
        spdlog::error("Error opening the file");
        return false;
    }

    file.write(password->data(), password->size());

    if (file.fail()) {
        spdlog::error("Problem writing in file");
        file.close();
        return false;
    }

    file.close();

    spdlog::debug("Successfully saved password");
    return true;
}
