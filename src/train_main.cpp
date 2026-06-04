#include <filesystem>
#include<iostream>
#include "pipeline.hpp"

int main() {
    std::string mnist_path = "/Users/javierrivero/Dev/datasets/mnist-pngs";
    std::vector <std::string> paths = get_training_path(mnist_path, 10);
    std::cout << "Got " << paths.size() << " training paths.\n";


    Matrix training_matrix;
    training_matrix.rows = paths.size();
    training_matrix.cols = 784;
    training_matrix.data.resize(training_matrix.rows * training_matrix.cols);

    try {
        for (size_t p = 0; p < paths.size(); p++) {
            cv::Mat image = load_image(paths[p]);
            Matrix pixels = to_pixel_matrix(image);
            std::copy(pixels.data.begin(), pixels.data.end(),training_matrix.data.begin() + p * 784);

            /*for (size_t j = 0; j < 784; j++) {
                training_matrix.data[p * 784 + j] = pixels.data[j];
            }*/
        }
        std::cout << "Loaded " << paths.size() << " images into training matrix\n";
        std::cout << "Training matrix: " << training_matrix.rows
                  << " x " << training_matrix.cols << "\n";
        std::cout << "First pixel of first image: " << training_matrix.data[0] << "\n";
        std::cout << "First pixel of last image:  " << training_matrix.data[99 * 784] << "\n";
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }


    return 0;
}
