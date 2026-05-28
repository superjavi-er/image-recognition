#include "pipeline.hpp"
#include <iostream>

int main() {
    try {
        cv::Mat image = load_image("data/sample.jpg");
        std::cout << "Loaded image: " << image.cols << "x" << image.rows << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;

}
