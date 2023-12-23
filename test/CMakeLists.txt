cmake_minimum_required(VERSION 3.28.1)

project(stuck-app-test CXX)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ../include)