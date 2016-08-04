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

void display_img(const cv::Mat& image){
//    cout << "in display_img rows="<<image.rows << " cols="<<image.cols<< endl;
    for(int i = 0; i < image.rows; i++){
        const uchar* datas = image.ptr<uchar>(i);
        for(int j = 0; j < image.cols; j++){
            cout<<(unsigned int)datas[j]<<", ";
        }
        cout<<endl;
    }
}

void display_img_double(const cv::Mat& image){
//    cout << "in display_img rows="<<image.rows << " cols="<<image.cols<< endl;
    for(int i = 0; i < image.rows; i++){
        const double* datas = image.ptr<double>(i);
        for(int j = 0; j < image.cols; j++){
            cout<<(double)datas[j]<<", ";
        }
        cout<<endl;
    }
}

double cacle_target_mean(cv::Mat& img){
    double sum = 0;
    double total =0;
    for(int i = 0; i < img.rows; i++){
        const uchar* datas = img.ptr<uchar>(i);
        for(int j = 0; j < img.cols; j++){
            if((unsigned int)datas[j]!=0){
                sum += (unsigned int)datas[j];
                total++;
            }
        }
    }
    return  sum/total;
}

void mat_add(cv::Mat& origin, cv::Mat& dist_mat){
    for(int i = 0; i< origin.rows; i++){
        for(int j=0; j< origin.cols; j++){
            dist_mat.at<double>(i,j) += origin.at<uchar>(i, j);
        }
    }
}

void cacle_img_means(string path_origin, cv::Mat& results){
    path p(path_origin);
    string sub_path;
    cv::Mat temp, img;
    temp = results.clone();
    temp.convertTo(temp,CV_64FC1,1/255.0);
    string save_path = "/home/aurora/hdd/workspace/data/test_mean_file/128*128_test_meanfile.jpg";
    int total = 0;
    for(int i = 0; i< temp.rows; i++){
        for(int j=0; j< temp.cols; j++){
            temp.at<double>(i, j) = 0;
        }
    }
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
    {
        sub_path = i->path().string();
        if (!is_directory(sub_path))
        {
            img = cv::imread(sub_path, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
            mat_add(img, temp);
            total++;
        }
    }
    display_img_double(temp/total);
    temp = temp/total;
    cv::imwrite(save_path, temp);
}

double cacle_pixel_mean(string path_origin, int row, int col){
    double sum = 0;
    int total = 0;
    path p(path_origin);
    string sub_path;
    cv::Mat img;
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
    {
        sub_path = i->path().string();
        if (!is_directory(sub_path))
        {
            img = cv::imread(sub_path, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
            sum += img.at<uchar>(row, col);
//            cout << sum <<",";
            total++;
        }
    }
    return sum/total;
}

void cacle_pixel_means(int rows, int cols, string path_origin, cv::Mat& mean_pic){
    double result_d = 0;
    string save_path = "/home/aurora/hdd/workspace/data/test_mean_file/128*128_test_meanfile.jpg";
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            result_d = cacle_pixel_mean(path_origin, i, j);
            cout << result_d<<", ";
            mean_pic.at<uchar>(i, j) = (unsigned char)result_d;

        }
    }
    display_img(mean_pic);
    cv::imwrite(save_path, mean_pic);
//    return results;
}


double total_mean(string path_origin){
    path p(path_origin);
    double totals = 0;
    int count = 0;
    string sub_path;
    cv::Mat img;
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
    {
        sub_path = i->path().string();
        if (!is_directory(sub_path))
        {
            img = cv::imread(sub_path, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
            double mean_value = cacle_target_mean(img);
            cout<<mean_value<<" , ";
            totals+=mean_value;
            count++;
        }
    }
    return totals/count;
}

void do_convert1(string original, string dist, double total){
    path p(original);
    cv::Mat img;
    cv::Mat target;
    string name, sub_path, dist_path;
    double img_mean = 0;
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
    {
        sub_path = i->path().string();
        name = i->path().filename().string();
        if (!is_directory(sub_path))
        {
//            cout<<sub_path<<endl;
            img = cv::imread(sub_path, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
            img_mean = cacle_target_mean(img);
            target = img*(img_mean/total);
            cout<<"image rows: "<<img.rows<<" img cols: "<<img.cols<<" img channels:"<<img.channels()<<" img type:"<<img.type()<<endl;
            cout<<"image rows: "<<target.rows<<" img cols: "<<target.cols<<" img channels:"<<target.channels()<<" img type:"<<target.type()<<endl;
            cv::imwrite(dist+name, target);
        }
    }
}


void do_convert2(string original, string dist, cv::Mat& mean){
    path p(original);
    cv::Mat img;
    cv::Mat target;
    string name, sub_path, dist_path;
    double img_mean = 0;
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
    {
        sub_path = i->path().string();
        name = i->path().filename().string();
        if (!is_directory(sub_path))
        {
            img = cv::imread(sub_path, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
            target = img - mean;
            target = target/mean;
            display_img(target);
            cv::imwrite(dist+name, target);
        }
    }
}

void do_convert3(string original, string dist, cv::Mat& mean){
    path p(original);
    cv::Mat img;
    cv::Mat target;
    string name, sub_path, dist_path;
    double ratio_val, mean_val = 0, ratio, img_val;
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
    {
        sub_path = i->path().string();
        name = i->path().filename().string();
        if (!is_directory(sub_path))
        {
            img = cv::imread(sub_path, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
            target = img - mean;
            for(int i=0; i < target.rows; i++){
                for(int j=0; j<target.cols; j++){
                    img_val = img.at<uchar>(i, j);
                    ratio_val = target.at<uchar>(i, j);
                    mean_val = mean.at<uchar>(i, j);
                    ratio = ratio_val/mean_val;
                    if(ratio_val>=0){
                        target.at<uchar>(i, j) = (unsigned char)(img_val-ratio*mean_val*0.3);
                    }else{
                        target.at<uchar>(i, j) = (unsigned char)(img_val+ratio*mean_val*0.5);
                    }
                }
            }
//            target = target/mean;
//            display_img(target);
            cv::imwrite(dist+name, target);
        }
    }
}

void do_convert4(string original, string dist, cv::Mat& mean){
    // left 16,33  right 112,95
    path p(original);
    cv::Mat img;
    cv::Mat target;
    string name, sub_path, dist_path;
    double ratio_val, mean_val = 0, ratio, img_val;
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
    {
        sub_path = i->path().string();
        name = i->path().filename().string();
        if (!is_directory(sub_path))
        {
            img = cv::imread(sub_path, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
            target = img - mean;
            for(int i=0; i < target.rows; i++){
                if(i>16||i<112){
                    continue;
                }
                for(int j=0; j<target.cols; j++){
                    if(j>33||j<95){
                        continue;
                    }
                    if(i>16||i<112){
                        cout<< i<<"--------------------"<<endl;
                    }
                    if(j>33||j<95){
                        cout<<j<<"----------------------"<<endl;
                    }
                    img_val = img.at<uchar>(i, j);
                    ratio_val = target.at<uchar>(i, j);
                    mean_val = mean.at<uchar>(i, j);
                    ratio = ratio_val/mean_val;
                    if(ratio_val>=0){
                        target.at<uchar>(i, j) = (unsigned char)(img_val-ratio*mean_val*0.3);
                    }else{
                        target.at<uchar>(i, j) = (unsigned char)(img_val+ratio*mean_val*0.6);
                    }
                }
            }
//            target = target/mean;
//            display_img(target);
            cv::imwrite(dist+name, target);
        }
    }
}

int main(){
    const string origin_test_path = "/home/aurora/hdd/workspace/data/sar_data_test/sar_total_data_test_128_128/";
    const string origin_test_img_path = "/home/aurora/hdd/workspace/data/sar_data_test/sar_total_data_test_128_128/HB03787#TRAIN#BMP2#SN_9563#17_DEG.JPG";
    const string mean_test_128_path = "/home/aurora/hdd/workspace/data/sar_data_test/test_mean_file/128_128_test_meanfile.jpg";
    const string dist_convert_test_path = "/home/aurora/hdd/workspace/data/sar_data_test/sar_total_data_test_128_128_convert1/";
    const string dist_convert_test_path2 = "/home/aurora/hdd/workspace/data/sar_data_test/sar_total_data_test_128_128_convert2/";
    const string dist_convert_test_path3 = "/home/aurora/hdd/workspace/data/sar_data_test/sar_total_data_test_128_128_convert3/";
    const string dist_convert_test_path4 = "/home/aurora/hdd/workspace/data/sar_data_test/sar_total_data_test_128_128_convert4/";
    const string file_test_path = "/home/aurora/hdd/workspace/data/sar_data_test/mean_file_testssssss/";

    cv::Mat temp_pic = cv::imread(origin_test_img_path, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    cv::Mat mean_pic = cv::imread(mean_test_128_path, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

    //caculate mean file
//    display_img(mean_pic);
//    cacle_pixel_means(128, 128, origin_test_path, mean_pic);
//    cacle_img_means(origin_test_path, temp_pic);

//    double total_m = total_mean(origin_test_path);
//    do_convert2(origin_test_path, dist_convert_test_path2, mean_pic);
    do_convert3(origin_test_path, dist_convert_test_path3, mean_pic);
//    do_convert3(file_test_path, dist_convert_test_path3, mean_pic);
//    do_convert4(origin_test_path, dist_convert_test_path4, mean_pic);


//    cv::Mat img1(3, 3, CV_8UC1, 3);
//    cv::Mat img2(3, 3, CV_8UC1, 2);
//    cv::Mat img3(3, 3, CV_64FC1, 1);
//    img1.at<uchar>(1, 1) = (unsigned char)100;
//    display_img(img1);
//    display_img(img2);
//    display_img_double(img3);
//    mat_add(img1, img3);
//    mat_add(img2, img3);
//    cout<<"_______"<<endl;
//    display_img(img1);
//    display_img(img2);
//    display_img_double(img3);
//    display_img(img2/img1);
//    cout<<"image rows: "<<img1.rows<<" img cols: "<<img1.cols<<" img channels:"<<img1.channels()<<" img type:"<<img1.type()<<endl;
//    cout<<"image rows: "<<img2.rows<<" img cols: "<<img2.cols<<" img channels:"<<img2.channels()<<" img type:"<<img2.type()<<endl;
//    cout<<"image rows: "<<img3.rows<<" img cols: "<<img3.cols<<" img channels:"<<img3.channels()<<" img type:"<<img3.type()<<endl;


    return 0;
}