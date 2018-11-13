#include "find_matches.h"
#include <string>
#include "utility.cpp"

using namespace std;
using namespace cv;
using namespace my_du;

int main () {
    const string img1_path = "/home/gosing/Desktop/backup-disk/dataset/kitti/training/image_02/";
    const string img2_path = "/home/gosing/Desktop/backup-disk/dataset/kitti/training/image_03/";
    const string n_sequence = "0010/";
    const string n_img = "000265.png";

    Mat img1, img2;
    string img1_s = img1_path + n_sequence + n_img;
    string img2_s = img2_path + n_sequence + n_img;
    img1 = cv::imread(img1_s, 1);
    img2 = cv::imread(img2_s, 1);

    FindMatches matcher (img1, img2);
    matcher.findORBMatches();
    vector<Point2f> p1, p2;
    matcher.getPointMatches(p1, p2);
    vector<KeyPoint> kp1, kp2;
    matcher.getKeyPointMatches(kp1, kp2);

    // show features points
    vis_keypoins(img1, img2, kp1, kp2);


}