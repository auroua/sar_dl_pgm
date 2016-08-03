#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <stdlib.h>
#include "boost/filesystem.hpp"

using namespace std;
using namespace boost::filesystem;

void getPath(vector<string>* base_path){
//    base_path->push_back("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/");
    base_path->push_back("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/");
    base_path->push_back("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/");
    base_path->push_back("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD1/");
    base_path->push_back("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD2/");
//    base_path->push_back("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/");
}

void gen_filename(map<string, string>* file_name_map){
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/31_DEG/COL2/SCENE1/SLICY", "SLICY#31_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/44_DEG/COL2/SCENE1/SLICY", "SLICY#44_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/29_DEG/COL2/SCENE1/SLICY", "SLICY#29_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/16_DEG/COL2/SCENE1/SLICY", "SLICY#16_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/43_DEG/COL2/SCENE1/SLICY", "SLICY#43_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/17_DEG/COL2/SCENE1/SLICY", "SLICY#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/30_DEG/COL2/SCENE1/SLICY", "SLICY#30_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/15_DEG/COL2/SCENE1/SLICY", "SLICY#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/45_DEG/COL2/SCENE1/SLICY", "SLICY#45_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/15_DEG/COL2/SCENE1/ZSU_23_4", "ZSU_23_4#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/15_DEG/COL2/SCENE1/ZIL131", "ZIL131#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/15_DEG/COL2/SCENE1/T62", "T62#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/15_DEG/COL2/SCENE1/BRDM_2", "BRDM_2#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/15_DEG/COL1/SCENE1/BTR_60", "BTR_60#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/15_DEG/COL2/SCENE1/D7", "D7#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/15_DEG/COL2/SCENE1/2S1", "2S1#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/45_DEG/COL2/SCENE1/2S1", "2S1#45_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/45_DEG/COL2/SCENE1/ZSU_23_4", "SC1#ZSU_23_4#45_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/45_DEG/COL2/SCENE2/ZSU_23_4", "SC2#ZSU_23_4#45_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/45_DEG/COL2/SCENE1/BRDM_2", "SC1#BRDM_2#45_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/45_DEG/COL2/SCENE3/BRDM_2", "SC3#BRDM_2#45_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/17_DEG/COL2/SCENE1/ZIL131", "ZIL131#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/17_DEG/COL2/SCENE1/T62", "T62#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/17_DEG/COL2/SCENE1/ZSU_23_4", "ZSU_23_4#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/17_DEG/COL2/SCENE1/BRDM_2", "BRDM_2#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/17_DEG/COL2/SCENE1/D7", "D7#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/17_DEG/COL2/SCENE1/2S1", "2S1#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/17_DEG/COL1/SCENE1/BTR_60", "BTR_60#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/30_DEG/COL2/SCENE1/ZSU_23_4", "SC1#ZSU_23_4#30_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/30_DEG/COL2/SCENE1/BRDM_2", "SC1#BRDM_2#30_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/30_DEG/COL2/SCENE1/2S1", "2S1#30_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/30_DEG/COL2/SCENE3/BRDM_2", "SC3#BRDM_2#30_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/30_DEG/COL2/SCENE2/ZSU_23_4", "SC2#ZSU_23_4#30_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD1/15_DEG/COL2/SCENE1/A62", "T72#A62#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD1/15_DEG/COL2/SCENE1/A10", "T72#A10#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD1/15_DEG/COL2/SCENE1/A07", "T72#A07#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD1/15_DEG/COL2/SCENE1/A32", "T72#A32#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD1/15_DEG/COL2/SCENE1/A64", "T72#A64#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD1/15_DEG/COL2/SCENE1/A04", "T72#A04#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD1/15_DEG/COL2/SCENE1/A05", "T72#A05#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD1/15_DEG/COL2/SCENE1/A63", "T72#A63#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD1/45_DEG/COL2/SCENE1/A64", "SC1#T72#A64#45_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD1/45_DEG/COL2/SCENE3/A64", "SC3#T72#A64#45_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD2/17_DEG/COL2/SCENE1/A62", "T72#A62#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD2/17_DEG/COL2/SCENE1/A10", "T72#A10#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD2/17_DEG/COL2/SCENE1/A07", "T72#A07#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD2/17_DEG/COL2/SCENE1/A32", "T72#A32#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD2/17_DEG/COL2/SCENE1/A64", "T72#A64#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD2/17_DEG/COL2/SCENE1/A04", "T72#A04#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD2/17_DEG/COL2/SCENE1/A05", "T72#A05#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD2/17_DEG/COL2/SCENE1/A63", "T72#A63#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD2/30_DEG/COL2/SCENE1/A64", "SC1#T72#A64#30_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_T_72_VARIANTS_CD2/30_DEG/COL2/SCENE3/A64", "SC3#T72#A64#30_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TRAIN/17_DEG/BTR70/SN_C71", "TRAIN#BTR70#SN_C71#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TRAIN/17_DEG/T72/SN_S7", "TRAIN#T72#SN_S71#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TRAIN/17_DEG/T72/SN_132", "TRAIN#T72#SN_132#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TRAIN/17_DEG/T72/SN_812", "TRAIN#T72#SN_812#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TRAIN/17_DEG/BMP2/SN_9563", "TRAIN#BMP2#SN_9563#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TRAIN/17_DEG/BMP2/SN_9566", "TRAIN#BMP2#SN_9566#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TRAIN/17_DEG/BMP2/SN_C21", "TRAIN#BMP2#SN_C21#17_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TEST/15_DEG/BTR70/SN_C71", "TEST#BTR70#SN_C71#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TEST/15_DEG/T72/SN_S7", "TEST#T72#SN_S7#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TEST/15_DEG/T72/SN_132", "TEST#T72#SN_132#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TEST/15_DEG/T72/SN_812", "TEST#T72#SN_812#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TEST/15_DEG/BMP2/SN_9563", "TEST#BMP2#SN_9563#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TEST/15_DEG/BMP2/SN_9566", "TEST#BMP2#SN_9566#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TEST/15_DEG/BMP2/SN_C21", "TEST#BMP2#SN_C21#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/SLICY/15_DEG", "SLICY#T72_BMP2_BTR70#15_DEG.JPG"));
    file_name_map->insert(make_pair("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/SLICY/30_DEG", "SLICY#T72_BMP2_BTR70#30_DEG.JPG"));
}

void read_dir(string& base_path, vector<string>* target_dir, bool filter_HTM, bool filter_SLICY){
    // filter string is HTMPICS and SLICY
    // if filter_HTM is true and sub_path contains HTM then do filter
    // if filter_SLICY is true and sub_path contains SLICY then do filter
    string filter_string1 = "HTMPICS";
    string filter_string2 = "SLICY";
    path p(base_path);
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
    {
        if (is_directory(i->path()))
        {
            string sub_path = i->path().string();
            if(filter_HTM){
                if((int)sub_path.find(filter_string1)!=-1){
                    continue;
                }
            }else{
                if((int)sub_path.find("HTMPICS/")!=-1){
//                    cout<<sub_path<<endl;
                    target_dir->push_back(sub_path);
                }
            }
            if(filter_SLICY){
                if((int)sub_path.find(filter_string2)!=-1){
                    continue;
                }
            }else{
                if(((int)sub_path.find("SCENE1/S")!=-1)||((int)sub_path.find("SCENE2/S")!=-1)||((int)sub_path.find("SCENE3/S")!=-1)){
//                    cout<<sub_path<<endl;
                    target_dir->push_back(sub_path);
                }
            }
            if(((int)sub_path.find("SCENE1/S")!=-1)||((int)sub_path.find("SCENE2/S")!=-1)||((int)sub_path.find("SCENE3/S")!=-1)){
//                continue;
            }else{
                if(((int)sub_path.find("SCENE1/")!=-1)||((int)sub_path.find("SCENE2/")!=-1)||((int)sub_path.find("SCENE3/")!=-1)){
                    target_dir->push_back(sub_path);
//                    cout<<sub_path<<endl;
                }
            }
//            cout<<sub_path<<endl;
            read_dir(sub_path, target_dir, filter_HTM, filter_SLICY);
        }
    }
}

bool find_target(const string& file_dir){
    vector<string> targets;
    targets.push_back("SN_C71");
    targets.push_back("SN_S7");
    targets.push_back("SN_132");
    targets.push_back("SN_812");
    targets.push_back("SN_9563");
    targets.push_back("SN_9566");
    targets.push_back("SN_C21");
    for(auto target = targets.begin(); target<targets.end(); target++){
        if((int)file_dir.find(*target)!=-1){
            return true;
        }
    }
    return false;
}

void read_dir_mixture(string& base_path, vector<string>* target_dir, bool filter_test, bool filter_HTM, bool filter_SLICY){
    string filter_string1 = "TEST";
    string filter_string2 = "SLICY/SLICY";
    string filter_string3 = "HTMPICS";
    path p(base_path);
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
    {
        if (is_directory(i->path()))
        {
            string sub_path = i->path().string();
            if(filter_HTM){
                if((int)sub_path.find(filter_string3)!=-1){
                    continue;
                }
            }
            if(filter_test){
                if((int)sub_path.find(filter_string1)!=-1){
                    continue;
                }
            }else{
                if(find_target(sub_path)&&((int)sub_path.find(filter_string1)!=-1)){
//                    cout<<sub_path<<endl;
                    target_dir->push_back(sub_path);
                }
            }
            if(filter_SLICY){
                if((int)sub_path.find(filter_string2)!=-1){
                    continue;
                }
            }else{
                if(((int)sub_path.find("SLICY/15_DEG")!=-1)||((int)sub_path.find("SLICY/30_DEG")!=-1)){
//                    cout<<sub_path<<endl;
                    target_dir->push_back(sub_path);
                }
            }
            if((int)sub_path.find("TEST")!=-1){
//                continue;
            }else{
                if(find_target(sub_path)){
//                    cout<<sub_path<<endl;
                    target_dir->push_back(sub_path);
                }
            }
//            cout<<sub_path<<endl;
            read_dir_mixture(sub_path, target_dir, filter_test, filter_HTM, filter_SLICY);
        }
    }
}

void read_file(string& base_path, vector<string> target_file, map<string, vector<string>>* files, string filename){
    path p(base_path);
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
    {
        if (!is_directory(i->path()))
        {
            string sub_path = i->path().string();
            if((sub_path.find("JPG")!=-1)||(sub_path.find("HTM")!=-1)||(sub_path.find("ERROR")!=-1)){
                continue;
            }
            target_file.push_back(sub_path);
//            cout<<sub_path<<endl;
        }
    }
    files->insert(make_pair(filename, target_file));
}

void display_map(map<string, vector<string>>& temp){
    for(auto iElement = temp.cbegin(); iElement!=temp.cend(); iElement++){
        cout<<iElement->first<<" total "<<iElement->second.size()<<endl;
        for(auto vec_Elemetn = iElement->second.cbegin(); vec_Elemetn!=iElement->second.cend(); vec_Elemetn++){
            cout<< "file path is ==="<< *vec_Elemetn <<endl;
        }
    }
}

void convert_image(map<string, vector<string>>& temp, string dist_path, string base_commond){
    string dist;
    string commond;
    int begin_index = 0;
    int end_index = 0;
    string temp_str;
    for(auto iElement = temp.cbegin(); iElement!=temp.cend(); iElement++){
        cout<<iElement->first<<" total "<<iElement->second.size()<<endl;
        for(auto vec_Elemetn = iElement->second.cbegin(); vec_Elemetn!=iElement->second.cend(); vec_Elemetn++){
//            cout<< "file path is ==="<< *vec_Elemetn;
//            if(vec_Elemetn->find("HB")==-1){
//                cout<< "file path is ==="<< *vec_Elemetn <<endl;
//            }
            commond = "";
            temp_str = "";
            dist = "";
            begin_index = vec_Elemetn->find("HB");
            end_index = vec_Elemetn->find(".") - begin_index;
            temp_str = vec_Elemetn->substr(begin_index, end_index);
//            cout<< "/////"<<temp_str<<endl;
            commond = base_commond+"  "+*vec_Elemetn+"  -o ";
            dist = dist_path + temp_str + "#" + iElement->first;
            commond = commond + dist + "   -e   -qf";
            system(commond.c_str());
        }
    }
}

int main(){
    const bool b_HTM = true;
    const bool b_SLICY = false;
    vector<string> base_path;
    vector<string> target_dir;

    const string dist_path = "/home/aurora/hdd/workspace/data/sar_total_data/";
    const string commond = "/home/aurora/hdd/workspace/data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/mstar2jpeg/mstar2jpeg -i";
    map<string, vector<string>> files;
    map<string, string> file_names;
    getPath(&base_path);
    for(auto path_ = base_path.begin(); path_<base_path.end(); path_++){
        read_dir(*path_, &target_dir, b_HTM, b_SLICY);
    }
    string mixture_target = "/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/";
    read_dir_mixture(mixture_target, &target_dir, false, b_HTM, b_SLICY);
    gen_filename(&file_names);

    for(auto dir = target_dir.begin(); dir<target_dir.end(); dir++){
        vector<string> target_file;
//        cout<< *dir << endl;
        auto iPairFound = file_names.find(*dir);
        if(iPairFound!=file_names.end()){
            read_file(*dir, target_file, &files, iPairFound->second);
        }
    }
//    display_map(files);

    convert_image(files, dist_path, commond);
    return 0;
}