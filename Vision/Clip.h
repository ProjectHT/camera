/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Clip.h
 * Author: phamh
 *
 * Created on July 2, 2018, 10:58 AM
 */

#ifndef CLIP_H
#define CLIP_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sys/time.h>
#include <opencv/cv.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Clip {
public:
    Clip(Size size_frame);
    Clip(const Clip& orig);
    virtual ~Clip();
    
    string getNameFile();
    void writeImage(Mat& frame);
    void putFrame(Mat& frame);
    void stop();
private:
    VideoWriter m_clip;
    string getDayTime();
    string name_file;
};

#endif /* CLIP_H */

