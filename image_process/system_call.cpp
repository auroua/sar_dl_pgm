//
// Created by aurora on 16-8-3.
//
//#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
void write_filename(char* dir){
    system(dir);
}

int main()
{
//    system("/home/aurora/hdd/workspace/data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/mstar2jpeg/mstar2jpeg -i /home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/17_DEG/COL2/SCENE1/ZSU_23_4/HB19491.026"
//                   " -o /home/aurora/hdd/workspace/data/sar_total_data/HB194913.JPG -e -qf");
////    char* dir = "ls /home/auroua/workspace/matlab/SAR-Data/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TEST/15_DEG/T72/SN_S7/ > /home/auroua/workspace/matlab/SAR-Data/filenames/15_SN_S7.txt";
//    write_filename(dir);

    system("/home/aurora/hdd/workspace/data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/mstar2jpeg/mstar2jpeg -i  /home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/15_DEG/COL2/SCENE1/2S1/HB14992.000  -o /home/aurora/hdd/workspace/data/sar_total_data/HB14992#2S1#15_DEG.JPG   -e   -qf");
}