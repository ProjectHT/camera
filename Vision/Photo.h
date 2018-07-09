/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Photo.h
 * Author: phamh
 *
 * Created on July 9, 2018, 1:55 PM
 */

#ifndef PHOTO_H
#define PHOTO_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sys/time.h>
#include <opencv/cv.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Photo {
public:
    Photo();
    Photo(const Photo& orig);
    virtual ~Photo();
    
    string writeImage(Mat& frame,string name, int index);
private:
    string getDayTime();
};

#endif /* PHOTO_H */

