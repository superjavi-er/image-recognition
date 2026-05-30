#include "pipeline.hpp"
#include <iostream>

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

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;

}
