cmake_minimum_required(VERSION 3.13)
project(AP)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/crypto.cpp
        src/unit_test.cpp
        src/message.cpp
        src/user.cpp
        src/server.cpp
)
target_link_libraries(main
        GTest::GTest
        GTest::Main
        OpenSSL::SSL
)