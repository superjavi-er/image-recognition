#include"pipeline.hpp"

std::vector<double> project_to_eigenspace(const Matrix& pixels, const Matrix& eigenbasis) {

    std::vector<double> result(eigenbasis.rows);
    for (int i = 0; i < eigenbasis.rows; i++) {
        double sum = 0.0;
        for (int j =0; j < eigenbasis.cols; j++) {
            sum += pixels.data[j] * eigenbasis.data[i * eigenbasis.cols +j];
        }
        result[i] = sum;
    }
    return result;
}