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
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;

}
