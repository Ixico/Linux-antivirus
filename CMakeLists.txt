cmake_minimum_required(VERSION 3.21)
project(Antivirus)

set(CMAKE_CXX_STANDARD 20)

add_executable(Antivirus main.cpp FileHasher.cpp FileHasher.h FileManager.cpp FileManager.h HashesDatabase.cpp HashesDatabase.h)

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)
