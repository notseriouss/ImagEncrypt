#include "headers/vernam_cipher.h"
#include "headers/options.h"
#include "spdlog/spdlog.h"

#include <boost/program_options.hpp>
#include <iostream>
#include <string>


namespace po = boost::program_options;


bool parseArguments(int argc, char* argv[], ProgramOptions& options) {
    po::options_description desc("IMAGE PROCESSOR - Process images with password authentication\n\nAllowed options");

    desc.add_options()
        ("help,h", "Show this help message and exit")
        ("input-image,i", po::value<std::string>(&options.input_image)->required(),
         "Input image file path")
        ("output-image,o", po::value<std::string>(&options.output_image)->required(),
         "Output image file path")
        ("password,p", po::value<std::string>(&options.password),
         "Use provided text as password")
        ("password-generate,g", po::bool_switch(&options.password_generate),
         "Generate a random password automatically")
        ("password-from,f", po::value<std::string>(&options.password_from),
         "Read password from specified file")
    ;

    po::variables_map vm;

    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
            std::cout << "Examples:\n";
            std::cout << "  " << argv[0] << " -i input.jpg -o output.jpg -p secret\n";
            std::cout << "  " << argv[0] << " --input-image=in.png --output-image=out.png --password-generate\n";
            std::cout << "  " << argv[0] << " -i img.bmp -o enc.bmp -f password.txt\n";
            return false;
        }


        po::notify(vm);


        int password_options = 0;
        if (vm.count("password")) password_options++;
        if (options.password_generate) password_options++;
        if (vm.count("password-from")) password_options++;

        if (password_options == 0) {
            throw po::error("One password option is required (--password, --password-generate, or --password-from)");
        } else if (password_options > 1) {
            throw po::error("Only one password option can be used at a time");
        }

        return true;

    } catch (const po::error& e) {
        spdlog::error("Error: {}", e.what());
        return false;
    }
}

int main(int argc, char* argv[]) {
    spdlog::set_pattern("%+");
    spdlog::set_level(spdlog::level::debug);

    ProgramOptions options;

    if (!parseArguments(argc, argv, options)) {
        return 1;
    }

    spdlog::debug("Successfully parsed logs");

    bool success = false;
    success = VernamCipher::encryptImage(options);

    return 0;
}
