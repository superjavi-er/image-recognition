#include"pipeline.hpp"
#include<opencv2/imgproc.hpp>
#include<vector>


Matrix to_pixel_matrix(const cv::Mat& image) {
    cv::Mat gray;
    cv::cvtColor(image,gray, cv::COLOR_BGR2GRAY);

    Matrix result;
    result.rows = 1;
    result.cols = gray.cols * gray.rows;
    result.data.resize(result.cols);

    for (int i = 0; i < gray.rows; i++) {
        for (int j = 0; j < gray.cols; j++) {
            result.data[i * gray.cols + j] = gray.at<uchar>(i,j);
        }
    }

    double sum = 0.0;
    for (int i = 0; i < result.cols; i++) {
        sum += result.data[i];
    }
    double mean = sum / result.cols;

    for (int i =0; i < result.cols; i++) {
        result.data[i] -= mean;
    }

    return result;
}