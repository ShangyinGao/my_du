#include "find_matches.h"

using namespace std;
using namespace cv;
using namespace my_du;

void FindMatches::findORBMatches () {
    vector<DMatch> matches, good_matches;
    Mat descriptor1, descriptor2;
    // 1. extract feature and descriptor
//    // method 1. detect in sub-image, then for each feature point add (left, top)
    Ptr<ORB> detector = ORB::create(500, 1.2f, 3, 21);
    detector->detect (img1_gray, kp1);
    detector->detect (img2_gray, kp2);

    // method 2. good feature to track
//    vector<Point2f> p_left, p_right;
//    cv::goodFeaturesToTrack(img_left.colRange(box_left.left, box_left.right).rowRange(box_left.top, box_left.bottom), p_left, 500, 0.01, 2);
//    cv::goodFeaturesToTrack(img_right.colRange(box_left.left, box_left.right).rowRange(box_left.top, box_left.bottom), p_right, 500, 0.01, 2);
//    for (auto &p : p_left)
//        kp_left.emplace_back(p.x, p.y, 1.);
//    for (auto &p : p_right)
//        kp_right.emplace_back(p.x, p.y, 1.);

    // method 3. select the pixels with high gradients
//    cv::Mat gray = img_left.colRange(box_left.left, box_left.right).rowRange(box_left.top, box_left.bottom);
//    for ( int x=0; x<gray.cols; x++ )
//        for ( int y=0; y<gray.rows; y++ ) {
//            Eigen::Vector2d delta (
//                    gray.ptr<uchar>(y)[x+1] - gray.ptr<uchar>(y)[x-1],
//                    gray.ptr<uchar>(y+1)[x] - gray.ptr<uchar>(y-1)[x]
//            );
//            if ( delta.norm() < 50 )
//                continue;
//            kp_left.emplace_back(x, y, 1.);
//        }
//    gray = img_right.colRange(box_left.left, box_left.right).rowRange(box_left.top, box_left.bottom);
//    for ( int x=0; x<gray.cols; x++ )
//        for ( int y=0; y<gray.rows; y++ ) {
//            Eigen::Vector2d delta (
//                    gray.ptr<uchar>(y)[x+1] - gray.ptr<uchar>(y)[x-1],
//                    gray.ptr<uchar>(y+1)[x] - gray.ptr<uchar>(y-1)[x]
//            );
//            if ( delta.norm() < 50 )
//                continue;
//            kp_right.emplace_back(x, y, 1.);
//        }
//
//    for (auto &p : kp_left) {
//        p.pt.x += box_left.left;
//        p.pt.y += box_left.top;
//    }
//    for (auto &p : kp_right) {
//        p.pt.x += box_right.left;
//        p.pt.y += box_right.top;
//    }

    detector->compute (img1, kp1, descriptor1);
    detector->compute (img2, kp2, descriptor2);
    // 2. find match
    Ptr<DescriptorMatcher> matcher  = DescriptorMatcher::create("BruteForce-Hamming");
    matcher->match (descriptor1, descriptor2, matches);
    double min_dist=10000, max_dist=0;
    for ( int i = 0; i < descriptor1.rows; i++ ) {
        double dist = matches[i].distance;
        if ( dist < min_dist ) min_dist = dist;
        if ( dist > max_dist ) max_dist = dist;
    }
//    printf ( "-- Max dist : %f \n", max_dist );
//    printf ( "-- Min dist : %f \n", min_dist );
    for ( int i = 0; i < descriptor1.rows; i++ ) {
        if ( matches[i].distance <= max ( 2*min_dist, 30.0 ) ) {
            good_matches.push_back ( matches[i] );
        }
    }
    cout << "good matches number: " << good_matches.size() << endl;

    // 3. triangulation give relative rotation and translation
    // suppose we already good rotation and translation estimation (here by using calibrated stereo camera)
    for ( auto &m : good_matches ) {
        p1.emplace_back(kp1[m.queryIdx].pt);
        p2.emplace_back(kp2[m.trainIdx].pt);
    }

    // reject with F
    vector<uchar> status;
    cv::findFundamentalMat(p1, p2, FM_RANSAC, 3, 0.99, status);
    size_t j = 0;
    for (size_t i = 0; i < status.size(); i++) {
        if (status[i] && i != j) {
            kp1[j] = kp1[i];
            kp2[j] = kp2[i];
            j ++;
        }
    }
    kp1.resize(j);
    kp2.resize(j);
    cout << "after rejection, points number: " << kp1.size() << endl;
}

void FindMatches::getKeyPointMatches(std::vector<cv::KeyPoint> &kp1_, std::vector<cv::KeyPoint> &kp2_) const {
    kp1_ = kp1;
    kp2_ = kp2;
}

void FindMatches::getPointMatches(std::vector<cv::Point2f> &p1_, std::vector<cv::Point2f> &p2_) const {
    p1_ = p1;
    p2_ = p2;
}
