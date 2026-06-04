cmake_minimum_required(VERSION 3.16)
project(image_recognition LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the OpenCV we just installed
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

# Shared source files used by both executables
set(SHARED_SOURCES
        src/load_image.cpp
        src/pixel_matrix.cpp
        src/eigenspace.cpp
        src/hash.cpp
        src/training_data.cpp
)

add_executable(recognize src/recognize_main.cpp ${SHARED_SOURCES})
add_executable(train     src/train_main.cpp     ${SHARED_SOURCES})
add_executable(test      tests/test_pipeline.cpp  ${SHARED_SOURCES})

# Tell the compiler where to find headers, and which libraries to link
target_include_directories(recognize PRIVATE include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(recognize PRIVATE ${OpenCV_LIBS} Eigen3::Eigen)

target_include_directories(train PRIVATE include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(train PRIVATE ${OpenCV_LIBS} Eigen3::Eigen)

target_include_directories(test PRIVATE include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(test PRIVATE ${OpenCV_LIBS} Eigen3::Eigen)