#include"pipeline.hpp"
#include <filesystem>

std::vector<std::string> get_training_path(const std::string& dataset_path, int per_digit) {
    namespace fs = std::filesystem;
    std::vector<std::string> paths;
    paths.reserve(10 * per_digit);
    for (size_t d = 0; d < 10; d++) {
        int count =0;
        std::string subpath = dataset_path + "/train/" + std::to_string(d);
        for (const auto& entry : fs::directory_iterator(subpath)) {
            paths.push_back(entry.path().string());
            count++;
            if (count >= per_digit) break;
        }

    }
    return paths;
}