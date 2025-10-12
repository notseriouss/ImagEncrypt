#include "headers/vernam_cipher.h"
#include "headers/password_generator.h"
#include "headers/files.h"
#include "headers/options.h"
#include "spdlog/spdlog.h"



std::vector<uint8_t> VernamCipher::stringToBytes(ProgramOptions &options, std::vector<uint8_t> &data) {
    std::unique_ptr<std::string> password;

    if (!options.password.empty()) {
        password = std::make_unique<std::string>(options.password);

    } else if (options.password_generate) {
        password = GENERATEPASSWORD::get_password(data.size());
        GETPASSWORD::save_password(password);

    } else if (!options.password_from.empty()) {
        password = GETPASSWORD::from_file(options.password_from);
    }


    std::vector<uint8_t> bytes;
    for (char c : *password) {
        bytes.push_back(static_cast<uint8_t>(c));
    }

    spdlog::debug("Successfully loaded password");
    return bytes;
}

void VernamCipher::applyVernam(std::vector<uint8_t>& data, const std::vector<uint8_t>& key) {
    if (key.empty()) return;

    size_t keyLen = key.size();
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] ^= key[i % keyLen];
    }

    spdlog::debug("Successfully applied vernam");
}

bool VernamCipher::loadImageToBytes(const std::string& path, cv::Mat& image, std::vector<uint8_t>& pixels) {
    image = cv::imread(path);
    if (image.empty()) {
        spdlog::error("Could not open or find the image: {}", path);
        return false;
    }

    cv::Mat flatImage = image.reshape(1, image.total() * image.channels());
    pixels.assign(flatImage.data, flatImage.data + flatImage.total());

    spdlog::debug("Successfully loaded image");
    return true;
}

bool VernamCipher::saveBytesToImage(const std::vector<uint8_t>& pixels, const cv::Mat& originalImage, const std::string& path) {
    cv::Mat processedImage = cv::Mat(pixels).reshape(originalImage.channels(), originalImage.rows);
    processedImage.convertTo(processedImage, originalImage.type());


    bool success = cv::imwrite(path, processedImage);
    if (!success) {
        spdlog::error("Could not save image to: {}", path);
        return false;
    }
    spdlog::debug("Successfully saved image");
    return true;
}

bool VernamCipher::encryptImage(ProgramOptions &options) {
    cv::Mat image;
    std::vector<uint8_t> pixels;

    if (!loadImageToBytes(options.input_image, image, pixels)) {
        return false;
    }

    std::vector<uint8_t> keyBytes = stringToBytes(options, pixels);

    spdlog::info("Encrypting image: {}x{} (channels: {})", image.cols, image.rows, image.channels());
    spdlog::info("Password length: {} (key bytes: {})", keyBytes.size(), keyBytes.size());

    applyVernam(pixels, keyBytes);

    if (!saveBytesToImage(pixels, image, options.output_image)) {
        return false;
    }

    spdlog::info("Successfully encrypted image: {}", options.output_image);
    spdlog::info("Total pixels proccessed: {}", image.total());
    spdlog::info("Total bytes encrypted: {}", pixels.size());
    return true;
}


