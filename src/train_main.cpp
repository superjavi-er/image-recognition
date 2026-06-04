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

        // Compute global mean: for each pixel position, average across all images
        std::vector<double> mean(784, 0.0);
        for (size_t j = 0; j < 784; j++) {
            double sum = 0;
            for (size_t i = 0; i < paths.size(); i++) {
                sum += training_matrix.data[i * 784 + j];
            }
            mean[j] = sum / paths.size();
        }
        std::cout << "Mean computed. "
          << "Mean[0]=" << mean[0]          // background (top-left)
          << ", Mean[350]=" << mean[350]    // foreground (above center)
          << ", Mean[406]=" << mean[406]    // foreground (true center)
          << ", Mean[462]=" << mean[462]    // foreground (below center)
          << ", Mean[783]=" << mean[783]    // background (bottom-right)
          << "\n";

        for (size_t i = 0; i < paths.size(); i++) {
            for (size_t j = 0; j < 784; j++) {
                training_matrix.data[j + i * 784] -= mean[j];
            }
        }

        double col0_mean = 0, col406_mean = 0, col783_mean = 0;
        for (size_t i = 0; i < paths.size(); i++) {
            col0_mean   += training_matrix.data[i * 784 + 0];
            col406_mean += training_matrix.data[i * 784 + 406];
            col783_mean += training_matrix.data[i * 784 + 783];
        }
        col0_mean   /= paths.size();
        col406_mean /= paths.size();
        col783_mean /= paths.size();

        std::cout << "After centering, column means (should all be ~0):\n";
        std::cout << "  col 0:   " << col0_mean << "\n";
        std::cout << "  col 406: " << col406_mean << "\n";
        std::cout << "  col 783: " << col783_mean << "\n";





    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }


    return 0;
}
