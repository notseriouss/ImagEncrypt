cmake_minimum_required(VERSION 3.20)
project(VernamImageEncrypt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Boost_ARCHITECTURE -x64)
set(Boost_USE_STATIC_LIBS   ON)

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)

add_subdirectory(src/libs/spdlog)


if(OpenCV_FOUND)
    message(STATUS "OpenCV version: ${OpenCV_VERSION}")
    message(STATUS "OpenCV include directories: ${OpenCV_INCLUDE_DIRS}")
    message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
else()
    message(FATAL_ERROR "OpenCV not found. Please install OpenCV.")
endif()

add_executable(vernam_encrypt
    src/main.cpp
    src/vernam_cipher.cpp
    src/headers/vernam_cipher.h
    src/password_generator.cpp
    src/headers/password_generator.h
    src/files.cpp
    src/headers/files.h
    src/headers/options.h
)


target_link_libraries(vernam_encrypt ${OpenCV_LIBS} ${Boost_LIBRARIES} spdlog)

target_include_directories(vernam_encrypt PRIVATE ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})

install(TARGETS vernam_encrypt DESTINATION bin)
