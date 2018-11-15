#include <vector>
#include <sstream>
#include <string>
#include <memory>
#include <map>
#include <iostream>
#include <array>
#include <algorithm>
#include <fstream>
#include "utility.h"

namespace my_du {

    enum TYPE {Car, Person, DontCare};

    struct Detection {
        //Detection (int frame_, int track_id_, int type_, int truncated_, int occluded_, double alpha_,
        //           std::array<double, 4> bbox_, std::array<double, 3> dimensions_, std::array<double, 3> locations_,
        //           double rotation_y_, double score_) :
        //           frame(frame_), track_id(track_id_), type(type_), truncated(truncated_), occluded(occluded_), alpha(alpha_),
        //           bbox(bbox_), dimensions(dimensions_), location(locations_), rotation_y(rotation_y_), score(score_) {}
        int frame;
        int track_id;
        int type; // Car, Van, Truck, Pedestrian, Person_sitting, Cyclist, Tram, Misc, DontCare
        int truncated;
        int occluded;
        double alpha;
        std::array<double, 4> bbox; // left, top, right, bottom
        std::array<double, 3> dimensions; // height, width, length
        std::array<double, 3> location; // x, y, z
        double rotation_y;
        double score; // could missed
    };

    class ReadKitti {

    public:

        void read(const std::string file_path_);

        // for each detection pushFrame and pushObject
        void pushFrame(int frame_, const std::shared_ptr<Detection> &det_);

        void pushObject(int track_id_, const std::shared_ptr<Detection> &det_);

        // two methods to return detections
        // 1.
        void getDetectionPreFrame(int frame_, std::vector<std::shared_ptr<Detection>> &vec_frame_);

        // 2.
        void getDetectionPreObject(int track_id_, std::vector<std::shared_ptr<Detection>> &vec_object_);

        // return vector of all frame ids; i.e. index of `map_vec_frame`
        void getVecFrame(std::vector<int> &vec_frame_);

        // return vector of all object's track_id; i.e. index of `map_vec_object`
        void getVecObject(std::vector<int> &vec_object_);

    private:

        // use map to avoid consider whether index exist, directly map_[id].push_back(std::make_shared<Detection> det)
        // 1. for a specific frame -> vector of detections
        std::map<int, std::vector<std::shared_ptr<Detection>>> map_vec_frame;

        // 2. for a track_id -> vector of detections
        std::map<int, std::vector<std::shared_ptr<Detection>>> map_vec_object;

    };
}