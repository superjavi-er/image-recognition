#include<iostream>
#include"pipeline.hpp"

int main() {
    try {
        cv::Mat image = load_image("data/sample.jpg");
        std::cout << "Loaded image: " << image.cols << "x" << image.rows << "\n";

        Matrix pixels = to_pixel_matrix(image);
        std::cout << "Pixel matrix: " << pixels.rows << "x" << pixels.cols << "\n";
        std::cout << "First pixel value: " << pixels.data[0] << "\n";

        double check = 0.0;
        for (int i = 0; i < pixels.cols; i++) check += pixels.data[i];
        std::cout <<  "Mean after centering:" << check / pixels.cols << "\n";

        // --- Synthetic test for project_to_eigenspace ---
        Matrix test_pixels;
        test_pixels.rows = 1;
        test_pixels.cols = 4;
        test_pixels.data = {1.0, 2.0, 3.0, 4.0};

        Matrix test_basis;
        test_basis.rows = 2;
        test_basis.cols = 4;
        test_basis.data = {
            1.0, 0.0, 0.0, 0.0,   // row 0: selects first pixel
            0.0, 0.0, 1.0, 1.0    // row 1: sums last two pixels
        };

        std::vector<double> projected = project_to_eigenspace(test_pixels, test_basis);
        std::cout << "Projection test: [" << projected[0] << ", " << projected[1] << "]\n";
        std::cout << "Expected:        [1, 7]\n";

        std::string hash = compute_hash(projected);
        std::cout << "Hash: " << hash << "\n";

        // Test get_training_path
        std::string mnist_path = "/Users/javierrivero/Dev/datasets/mnist-pngs";
        std::vector<std::string> training_paths = get_training_path(mnist_path, 10);

        std::cout << "Got " << training_paths.size() << " training paths.\n";
        std::cout << "Training paths: " << training_paths.size() << "\n";
        std::cout << "First: " << training_paths.front() << "\n";
        std::cout << "Last:  " << training_paths.back() << "\n";

        Matrix training_matrix;
        training_matrix.rows = training_paths.size();
        training_matrix.cols = 784;
        training_matrix.data.resize(training_matrix.rows * training_matrix.cols);

        for (size_t p = 0; p < training_paths.size(); p++) {
            cv::Mat image = load_image(training_paths[p]);
            Matrix pixels = to_pixel_matrix(image);
            std::copy(pixels.data.begin(), pixels.data.end(),training_matrix.data.begin() + p * 784);

            /*for (size_t j = 0; j < 784; j++) {
                training_matrix.data[p * 784 + j] = pixels.data[j];
            }*/
        }
        std::cout << "Loaded " << training_paths.size() << " images into training matrix\n";
        std::cout << "Training matrix: " << training_matrix.rows
                  << " x " << training_matrix.cols << "\n";
        std::cout << "First pixel of first image: " << training_matrix.data[0] << "\n";
        std::cout << "First pixel of last image:  " << training_matrix.data[99 * 784] << "\n";

        // Compute global mean: for each pixel position, average across all images
        std::vector<double> mean(784, 0.0);
        for (size_t j = 0; j < 784; j++) {
            double sum = 0;
            for (size_t i = 0; i < training_paths.size(); i++) {
                sum += training_matrix.data[i * 784 + j];
            }
            mean[j] = sum / training_paths.size();
        }
        std::cout << "Mean computed. "
          << "Mean[0]=" << mean[0]          // background (top-left)
          << ", Mean[350]=" << mean[350]    // foreground (above center)
          << ", Mean[406]=" << mean[406]    // foreground (true center)
          << ", Mean[462]=" << mean[462]    // foreground (below center)
          << ", Mean[783]=" << mean[783]    // background (bottom-right)
          << "\n";

        for (size_t i = 0; i < training_paths.size(); i++) {
            for (size_t j = 0; j < 784; j++) {
                training_matrix.data[j + i * 784] -= mean[j];
            }
        }

        double col0_mean = 0, col406_mean = 0, col783_mean = 0;
        for (size_t i = 0; i < training_paths.size(); i++) {
            col0_mean   += training_matrix.data[i * 784 + 0];
            col406_mean += training_matrix.data[i * 784 + 406];
            col783_mean += training_matrix.data[i * 784 + 783];
        }
        col0_mean   /= training_paths.size();
        col406_mean /= training_paths.size();
        col783_mean /= training_paths.size();

        std::cout << "After centering, column means (should all be ~0):\n";
        std::cout << "  col 0:   " << col0_mean << "\n";
        std::cout << "  col 406: " << col406_mean << "\n";
        std::cout << "  col 783: " << col783_mean << "\n";







    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}