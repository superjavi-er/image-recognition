#include"pipeline.hpp"
#include<stdexcept>
#include<opencv2/imgcodecs.hpp>

cv::Mat load_image(const std::string& path) {
   cv::Mat image = cv::imread(path);
   if (image.empty()) {
      throw std::runtime_error("Failed to load image: " + path);
   }
   return image;
}


