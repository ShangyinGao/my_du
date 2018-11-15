#include "read_kitti.h"
#include "utility.h"

using namespace std;
using namespace my_du;

int main() {
    string det_root_path = "/home/gosing/Desktop/backup-disk/dataset/kitti/training/label_02/";
    int n_sqeuence = 15;
    vector<string> det_file_list;
    Utility::getdir(det_root_path, det_file_list);

    string det_path = det_root_path + det_file_list[n_sqeuence];
    cout << "detection file path: " << det_path << endl;

    ReadKitti reader;
    reader.read(det_path);

    // show result
    vector<int> vec_frame_id, vec_track_id;
    vector<shared_ptr<Detection>> frame, object;
    reader.getVecFrame(vec_frame_id);
    reader.getVecObject(vec_track_id);
    reader.getDetectionPreFrame(vec_frame_id.at(10), frame);
    reader.getDetectionPreObject(vec_track_id.at(1), object);

    int zimu;


#ifdef someTest
    // vector: swap
    // some methods to copy one vector to another
    // 1. use default constructor: vector<T> v2 (v1)
    // 2. use `swap`: vector<T> copy both used and unused memory
    // 3. use assignment constructor `=`
    cout << "======" << endl;
    for (int i = 0; i < 2; i++) {
        //vector<int> v{1, 2, 3, 4, 5, 6};
        vector<int> v;
        //v.reserve(10); // attention: reserve before loop push_back to avoid potentially multiple memory relocate
        for (int j = 0; j < 6; j++) {
            v.push_back(j);
        }
        cout << "origin vector" << endl;
        cout << "\tcapacity: " << v.capacity() << endl;
        cout << "\tsize: " << v.size() << endl;
        if (i == 0) {
            vector<int> v2;
            v2.swap(v);
            cout << "after swap" << endl;
            cout << "\tv2:" << endl;
            cout << "\tcapacity: " << v2.capacity() << endl;
            cout << "\tsize: " << v2.size() << endl;
        }
        if (i == 1) {
            vector<int> v3(v);
            v3.swap(v);
            cout << "after construct a new vector" << endl;
            cout << "\tv3: " << endl;
            cout << "\tcapacity: " << v3.capacity() << endl;
            cout << "\tsize: " << v3.size() << endl;
        }
        cout << "\tv: " << endl;
        cout << "\tcapacity: " << v.capacity() << endl;
        cout << "\tsize: " << v.size() << endl;
    }

    // vector
    // use list constructor: size = capacity
    // use `push_back` capacity double at each time size == capacity
    // use list constructor to init v to make v.size() == v.capacity() == 6, then `push_back` one element
    // what is the capacity?
    vector<int> v10 {1, 2, 3, 4, 5, 6};
    cout << "======" << endl;
    cout << "v10 size: "<< v10.size() << endl;
    cout << "v10 capacity: " << v10.capacity() << endl;
    cout << "after push_back one element:" << endl;
    v10.push_back(7);
    cout << "new size: " << v10.size() << endl;
    cout << "new capacity: " << v10.capacity() << endl;
#endif

    return 0;
}