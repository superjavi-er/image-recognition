#include"pipeline.hpp"

std::string compute_hash(const std::vector<double>& reduced) {
    std::string result;
    result.reserve(reduced.size());
    for (size_t i = 0; i < reduced.size(); i++) {
        result += (reduced[i] > 0.0) ? '1' : '0';
    }
    return result;
}