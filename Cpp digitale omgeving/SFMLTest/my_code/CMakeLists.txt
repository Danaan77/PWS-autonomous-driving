cmake_minimum_required(VERSION 3.20)

project(SFMLTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(SFMLTest main.cpp)

target_link_libraries(SFMLTest PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

add_custom_command(TARGET SFMLTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/Users/danie/OneDrive/Documents/VS code/Cpp digitale omgeving/sorcecode/SFML-3.1.0-windows-vc17-64-bit/SFML-3.1.0/bin"
        "$<TARGET_FILE_DIR:SFMLTest>"
)