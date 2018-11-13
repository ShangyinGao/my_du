#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <string>

namespace my_du {
    class FindMatches {
    public:
        FindMatches (const cv::Mat img1_, const cv::Mat img2_) {
            img1 = img1_;
            img2 = img2_;
            cv::cvtColor(img1, img1_gray, CV_BGR2GRAY);
            cv::cvtColor(img2, img2_gray, CV_BGR2GRAY);
        }

        void findORBMatches ();

        void getKeyPointMatches (std::vector<cv::KeyPoint> &kp1_, std::vector<cv::KeyPoint> &kp2_) const;

        void getPointMatches (std::vector<cv::Point2f> &p1_, std::vector<cv::Point2f> &p2_) const;

    private:
        std::vector<cv::KeyPoint> kp1, kp2;

        std::vector<cv::Point2f> p1, p2;

        cv::Mat img1, img2, img1_gray, img2_gray;
    };
}
