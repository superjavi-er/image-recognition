#include "pipeline.hpp"
#include <iostream>

int main() {
    try {
        cv::Mat image = load_image("data/sample.jpg");

        Matrix pixels = to_pixel_matrix(image);

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;

}
