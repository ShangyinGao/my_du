#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

class FindMatches {
public:
    FindMatches (const cv::Mat img1_, const cv::Mat img2_) {
        img1 = img1_.clone();
        img2 = img2_.clone();
        cv::cvtColor(img1, img1_gray, CV_BGR2GRAY);
        cv::cvtColor(img2, img2_gray, CV_BGR2GRAY);
    }

    void findORBMatches ();

    void getKeyPointMatches (std::vector<cv::KeyPoint> &kp1, std::vector<cv::KeyPoint> &kp2);

    void getPointMatches (std::vector<cv::Point2f> &p1, std::vector<cv::Point2f> &p2);

private:
    std::vector<cv::KeyPoint> match1, match2;

    std::vector<cv::Point2f> p1, p2;

    cv::Mat img1, img2, img1_gray, img2_gray;
};
