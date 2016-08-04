//
// Created by aurora on 16-8-4.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "boost/filesystem.hpp"

using namespace std;
using namespace boost::filesystem;

void do_resize(string original, string dist, int size){
    path p(original);
    cv::Mat img;
    cv::Mat target;
    cv::Size cv_size;
    cv_size.height = size;
    cv_size.width = size;
    string name, sub_path, dist_path;
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
    {
        sub_path = i->path().string();
        name = i->path().filename().string();
        if (!is_directory(sub_path))
        {
            cout<<sub_path<<endl;
            img = cv::imread(sub_path, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
//            cv::namedWindow("Image");
//            cv::imshow("image", img);
//            cv::waitKey(0);
            cv::resize(img, target, cv_size, 0, 0, CV_INTER_LINEAR);  //CV_INTER_AREA,CV_INTER_CUBIC,CV_INTER_NN
            cout<<"image rows: "<<img.rows<<" img cols: "<<img.cols<<" img channels:"<<img.channels()<<" img type:"<<img.type()<<endl;
            cout<<"image rows: "<<target.rows<<" img cols: "<<target.cols<<" img channels:"<<target.channels()<<" img type:"<<target.type()<<endl;
            cv::imwrite(dist+name, target);
        }
    }
}

int main(){
    const string origin_path = "/home/aurora/hdd/workspace/data/sar_total_data/";
    const string origin_test_path = "/home/aurora/hdd/workspace/data/sar_total_data_test/";
    const string dist_path = "/home/aurora/hdd/workspace/data/sar_total_data_128*128/";
    const string dist_test_path = "/home/aurora/hdd/workspace/data/sar_total_data_test_128*128/";

    const string original_440 = "/home/aurora/hdd/workspace/data/sar_data_test/sar_total_data_test_128_128_convert3/";
    const string dist_test_440 = "/home/aurora/hdd/workspace/data/sar_data_test/sar_total_data_test_440*440/";
    const int SIZE = 440;

//    do_resize(origin_path, dist_path, SIZE);
//    do_resize(origin_test_path, dist_test_path, SIZE);
    do_resize(original_440, dist_test_440, SIZE);
    return 0;
}