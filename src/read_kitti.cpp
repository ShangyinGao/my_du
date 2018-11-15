#include "read_kitti.h"

using namespace std;
using namespace my_du;

void ReadKitti::read(const std::string file_path_) {
    cout << "reading detection ..." << endl;
    std::ifstream infile(file_path_);
    std::string line;
    int i = 0;
    while (getline(infile, line)) {
        i++;
        istringstream iss(line);
        vector<string> vec_det;
        Utility::splitString(line, ' ', vec_det);
        auto det = std::make_shared<Detection>();
        det->frame = stoi(vec_det[0]);
        det->track_id = stoi(vec_det[1]);
        // Car, Van, Truck, Pedestrian, Person_sitting, Cyclist, Tram, Misc, DontCare
        string s_type = vec_det[2];
        if (s_type == "Car" || s_type == "Van" || s_type == "Truck")
            det->type = 0;
        else if (s_type == "Person_sitting" || s_type == "Cyclist")
            det->type = 1;
        else
            det->type = 2;
        det->truncated = stoi(vec_det[3]);
        det->occluded = stoi(vec_det[4]);
        det->alpha = stod(vec_det[5]);
        det->bbox[0] = stod(vec_det[6]);
        det->bbox[1] = stod(vec_det[7]);
        det->bbox[2] = stod(vec_det[8]);
        det->bbox[3] = stod(vec_det[9]);
        det->dimensions[0] = stod(vec_det[10]);
        det->dimensions[1] = stod(vec_det[11]);
        det->dimensions[2] = stod(vec_det[12]);
        det->location[0] = stod(vec_det[13]);
        det->location[1] = stod(vec_det[14]);
        det->location[2] = stod(vec_det[15]);
        det->rotation_y = stod(vec_det[16]);
        if (vec_det.size() == 18)
            det->score = stod(vec_det[17]);

        //
        pushFrame(det->frame, det);
        pushObject(det->track_id, det);
    }
    cout << "detection number: " << i << endl;
}

void ReadKitti::pushFrame(int frame_, const std::shared_ptr<my_du::Detection> &det_) {
    map_vec_frame[frame_].push_back(det_);
}

void ReadKitti::pushObject(int track_id_, const std::shared_ptr<my_du::Detection> &det_) {
    map_vec_object[track_id_].push_back(det_);
}

void ReadKitti::getDetectionPreFrame(int frame_, std::vector<std::shared_ptr<my_du::Detection>> &vec_frame_) {
    vec_frame_ = map_vec_frame[frame_];
}

void ReadKitti::getDetectionPreObject(int track_id_, std::vector<std::shared_ptr<my_du::Detection>> &vec_object_) {
    vec_object_ = map_vec_object[track_id_];
}

void ReadKitti::getVecFrame(std::vector<int> &vec_frame_) {
    vec_frame_.clear();
    for (int i = 0; ; i++) {
        auto it = map_vec_frame.find(i);
        if (it == map_vec_frame.end())
            break;
        vec_frame_.push_back(i);
    }
    sort(vec_frame_.begin(), vec_frame_.end());
}

void ReadKitti::getVecObject(std::vector<int> &vec_object_) {
    vec_object_.clear();
    for (int i = 0; ; i++) {
        auto it = map_vec_object.find(i);
        if (it == map_vec_object.end())
            break;
        vec_object_.push_back(i);
    }
    sort(vec_object_.begin(), vec_object_.end());
}