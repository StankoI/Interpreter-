cmake_minimum_required(VERSION 3.28.1)

project(stuck-app CXX)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ArrayValue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BoolValue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ExprTree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/NumValue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/StringValue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Tokinezer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Interpreter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/printCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/setCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/readCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/funcCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/EvalFunctions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ExprTreeBuilding.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/setArrayFunctions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/setBoolFunctions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/setNumFunctions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/setStringFunctions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/setExistingNodeFunction.cpp
    
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test.stuck ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_subdirectory(test)