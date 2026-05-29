#pragma once

#include<string>
#include<opencv2/core.hpp>
#include<vector>

struct Matrix {
    int rows;
    int cols;
    std::vector<double> data;
};

cv::Mat load_image(const std::string& path);

Matrix to_pixel_matrix(const cv::Mat& image);

std::vector<double> project_to_eigenspace(const Matrix& pixels, const Matrix& eigenbasis);