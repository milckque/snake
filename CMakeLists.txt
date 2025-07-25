cmake_minimum_required(VERSION 3.16)
project(snake)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Method 1: Using find_package with explicit Homebrew path (working!)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml")
find_package(SFML REQUIRED COMPONENTS System Window Graphics Network Audio)

# Create executable
add_executable(snake main.cpp)

# Link SFML libraries
target_link_libraries(snake SFML::System SFML::Window SFML::Graphics SFML::Network SFML::Audio)