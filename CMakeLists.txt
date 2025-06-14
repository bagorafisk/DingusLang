cmake_minimum_required(VERSION 3.10)

# Set project name and C++ standard
project(DingusLang LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header files
include_directories(include)

# Add source files
set(SOURCES
    src/main.cpp
    src/lexer.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

