/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InfoCamera.h
 * Author: Thong_Laptop
 *
 * Created on June 22, 2018, 10:45 AM
 */

#ifndef INFOCAMERA_H
#define INFOCAMERA_H

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class InfoCamera {
public:
    InfoCamera();
    InfoCamera(const InfoCamera& orig);
    virtual ~InfoCamera();
    
    string link_camera;
    string link_dir;
    string name_camera;
    Mat m_buffer;
    
    bool flag_run;
    bool flag_save;
    bool flag_vision;
    bool flag_data_ready;
    
    void init(string name, string link, string file);
    Mat getData();
    void setData(Mat& data);
private:
    Mat t_buffer;
};

#endif /* INFOCAMERA_H */

