#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <dirent.h>
#include <string.h>
#include <opencv2/opencv.hpp>

class Utility {

public:
    static cv::Scalar randomColor (cv::RNG &rng);

    static void vis_keypoins (const cv::Mat img1_, const cv::Mat img2_, const std::vector<cv::KeyPoint> &kp1_, const std::vector<cv::KeyPoint> &kp2_);

    static int getdir (std::string &dir, std::vector<std::string> &files);

    template<typename Out>
    static void split(const std::string &s, char delim, Out result);

    static void splitString(const std::string &s, char delim, std::vector<std::string> &ret);

};
