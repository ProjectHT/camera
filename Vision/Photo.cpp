/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Photo.cpp
 * Author: phamh
 * 
 * Created on July 9, 2018, 1:55 PM
 */

#include "Photo.h"

Photo::Photo() {
}

Photo::Photo(const Photo& orig) {
}

Photo::~Photo() {
}

string Photo::getDayTime() {
    timeval tp;
    gettimeofday(&tp, 0);
    time_t nowtime;
    nowtime = tp.tv_sec;
    struct tm *nowtm;
    nowtm = localtime(&nowtime);
    string m_return = std::to_string(nowtm->tm_mday);
    m_return += std::to_string(nowtm->tm_mon) + "-";
    m_return += std::to_string(nowtm->tm_year + 1900) + "_";
    m_return += std::to_string(nowtm->tm_hour) + "-";
    m_return += std::to_string(nowtm->tm_min) + "-";
    m_return += std::to_string(nowtm->tm_sec);
    return m_return;
}

string Photo::writeImage(Mat& frame,string name, int index) {
    vector<int> compression_params;
    compression_params.push_back( cv::IMWRITE_JPEG_QUALITY );
    compression_params.push_back( 100 );
    string name_data = name + "-" + std::to_string(index) + "-" + getDayTime() + ".jpg";
    string path = "/var/www/html/Face/" + name_data;
    imwrite(path.c_str(), frame, compression_params); 
    return name_data;
}