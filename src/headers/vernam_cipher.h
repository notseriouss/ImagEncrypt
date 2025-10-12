#pragma once

#include "options.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <cstdint>

class VernamCipher {
public:
    static bool encryptImage(ProgramOptions &options);

private:
    static std::vector<uint8_t> stringToBytes(ProgramOptions &options, std::vector<uint8_t> &data);

    static void applyVernam(std::vector<uint8_t>& data, const std::vector<uint8_t>& key);

    static bool loadImageToBytes(const std::string& path, cv::Mat& image, std::vector<uint8_t>& pixels);

    static bool saveBytesToImage(const std::vector<uint8_t>& pixels,
                                const cv::Mat& originalImage,
                                const std::string& path);
};
