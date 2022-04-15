cmake_minimum_required(VERSION 3.21)
project(Antivirus)

set(CMAKE_CXX_STANDARD 20)

add_executable(Antivirus main.cpp Source/FileHasher.cpp Headers/FileHasher.h Source/FileManager.cpp Headers/FileManager.h Controllers/FileController.cpp Headers/FileController.h Controllers/QuarantineController.cpp Headers/QuarantineController.h QuarantineRecord.cpp QuarantineRecord.h Headers/ConfigurationVariables.h Controllers/CLIController.cpp Headers/CLIController.h)

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)
