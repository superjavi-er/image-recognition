cmake_minimum_required(VERSION 3.16)
project(image_recognition LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the OpenCV we just installed
find_package(OpenCV REQUIRED)

# Build one executable named "recognize" from our source files
add_executable(recognize src/main.cpp)

# Tell the compiler where to find headers, and which libraries to link
target_include_directories(recognize PRIVATE include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(recognize PRIVATE ${OpenCV_LIBS})
