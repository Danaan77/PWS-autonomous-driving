
cmake_minimum_required(VERSION 3.20)
project(SFMLTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_ROOT "C:/Users/danie/OneDrive/Documents/PWS-autonomous-driving/Cpp digitale omgeving/sorcecode/SFML-2.6.2-windows-vc17-64-bit/SFML-2.6.2")

add_executable(SFMLTest my_code/Code_Joyce.cpp)

target_include_directories(SFMLTest PRIVATE "${SFML_ROOT}/include")

target_link_libraries(SFMLTest PRIVATE
    "${SFML_ROOT}/lib/sfml-graphics.lib"
    "${SFML_ROOT}/lib/sfml-window.lib"
    "${SFML_ROOT}/lib/sfml-system.lib"
)

add_custom_command(TARGET SFMLTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SFML_ROOT}/bin"
    "$<TARGET_FILE_DIR:SFMLTest>"
)
