#include <vector>
#include <opencv2/opencv.hpp>

static cv::Scalar randomColor (cv::RNG &rng) {
        int icolor = (unsigned) rng;
        return cv::Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

void vis_keypoins (const cv::Mat img1_, const cv::Mat img2_, const std::vector<cv::KeyPoint> &kp1_, const std::vector<cv::KeyPoint> &kp2_) {
    cv::Mat img1 = img1_.clone();
    cv::Mat img2 = img2_.clone();
    cv::RNG rng(12345);
    cv::drawKeypoints(img1, kp1_, img1);
    cv::drawKeypoints(img2, kp2_, img2);

    cv::imshow("img1 with keypoints", img1);
    cv::imshow("img2 with keypoints", img2);

    cv::waitKey(0);
}