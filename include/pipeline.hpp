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

std::string compute_hash(const std::vector<double>& reduced);

std::vector<std::string> get_training_path(const std::string& dataset_path, int per_digit);