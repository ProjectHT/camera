/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vision.h
 * Author: phamh
 *
 * Created on June 27, 2018, 10:21 AM
 */

#ifndef VISION_H
#define VISION_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sys/time.h>
#include <opencv/cv.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include "InfoVision.h"
#include "Clip.h"
#include "../Http/HTTPRequest.h"
#include "Photo.h"

using namespace std;
using namespace cv;

class Vision {
public:
    Vision(InfoVision* info);
    Vision(const Vision& orig);
    virtual ~Vision();
    
    void run();
    
    void loadInput();
    void initDetectPerson();
    void dectectPerson(Mat &input, vector<Rect> &area, int &offset_x, int &offset_y);
private:
    Mat background;
    Mat input;
    Mat src;
    Mat display;
    HOGDescriptor hog_detect_person;
    CascadeClassifier cascade;
    InfoVision* p_info_vision;
    Photo m_photo;
    
    double measureTime(timeval& begin, timeval& end);
    Mat morphologyOperations(Mat& in);
    void createBackground();
    bool detectObj();
    
    int getMs();
    void compressionParamsImage(vector<int>& compression_params);
    void saveImage(Mat& input, int index,vector<int>& compression_params);
    void dectectFace(Mat& input);
};

#endif /* VISION_H */

