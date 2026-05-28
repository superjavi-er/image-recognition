# Image Recognition Software (C++)

Image recognition built from scratch in C++ using an eigenfaces / PCA approach.
Images are loaded, converted to a pixel matrix, projected into a lower-dimensional
eigenspace, and reduced to a hash that can be compared against new uploads. The
eigenspace projection makes matching robust to small changes like rotation or scaling.

## Pipeline

1. load_image  - read an image file from disk
2. to_pixel_matrix  - convert the image into a 2D pixel matrix
3. project_to_eigenspace  - project the matrix into a lower-dimensional space
4. compute_hash  - reduce that to a hash for storage and comparison

## Branches

- from-scratch    - the linear algebra implemented by hand, to learn the math
- with-libraries  - using Eigen / Armadillo and OpenCV's built-in tools

## Build

Requires a C++17 compiler, CMake, and OpenCV.

    cmake -S . -B build
    cmake --build build
    ./build/recognize data/sample.jpg

## Status

Project scaffold. Implementation in progress, one function at a time.
