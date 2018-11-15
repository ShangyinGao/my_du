#include "utility.h"


cv::Scalar Utility::randomColor (cv::RNG &rng) {
    int icolor = (unsigned) rng;
    return cv::Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

void Utility::vis_keypoins (const cv::Mat img1_, const cv::Mat img2_, const std::vector<cv::KeyPoint> &kp1_, const std::vector<cv::KeyPoint> &kp2_) {
    cv::Mat img1 = img1_.clone();
    cv::Mat img2 = img2_.clone();
    cv::RNG rng(12345);
    cv::drawKeypoints(img1, kp1_, img1);
    cv::drawKeypoints(img2, kp2_, img2);

    cv::imshow("img1 with keypoints", img1);
    cv::imshow("img2 with keypoints", img2);

    cv::waitKey(0);
}

int Utility::getdir (std::string &dir, std::vector<std::string> &files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        if (dirp->d_name[0] == '.')
            continue;
        files.push_back(std::string(dirp->d_name));
    }
    closedir(dp);

    std::sort(files.begin(), files.end());

    return 0;
}

template<typename Out>
void Utility::split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

void Utility::splitString(const std::string &s, char delim, std::vector<std::string> &ret) {
    split(s, delim, std::back_inserter(ret));
}
