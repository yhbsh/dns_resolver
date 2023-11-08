cmake_minimum_required(VERSION 3.27.7)

project(dns_resolver C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Debug)

# Add an executable to the project using the specified source files.
add_executable(${PROJECT_NAME} src/dns_resolver.c)
