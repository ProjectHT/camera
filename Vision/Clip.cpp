/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Clip.cpp
 * Author: phamh
 * 
 * Created on July 2, 2018, 10:58 AM
 */

#include "Clip.h"

Clip::Clip(Size size_frame) {
    name_file = getDayTime();
    string path = "/var/www/html/Clip/" + name_file + ".avi";
    m_clip.open(path.c_str(), cv::VideoWriter::fourcc('X', '2', '6', '4'), 30, size_frame, true);
}

Clip::Clip(const Clip& orig) {
}

Clip::~Clip() {
}

string Clip::getDayTime() {
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

string Clip::getNameFile() {
    return name_file;
}

void Clip::putFrame(Mat& frame) {
    if(m_clip.isOpened())
        m_clip.write(frame);
}

void Clip::stop() {
    m_clip.release();
}

void Clip::writeImage(Mat& frame) {
    vector<int> compression_params;
    compression_params.push_back( cv::IMWRITE_JPEG_QUALITY );
    compression_params.push_back( 100 );
    string path = "/var/www/html/Clip/" + name_file + ".jpg";
    imwrite(path.c_str(), frame, compression_params); 
}