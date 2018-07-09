/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InfoCamera.cpp
 * Author: Thong_Laptop
 * 
 * Created on June 22, 2018, 10:45 AM
 */

#include "InfoCamera.h"

InfoCamera::InfoCamera() {
    flag_save = false;
}

InfoCamera::InfoCamera(const InfoCamera& orig) {
}

InfoCamera::~InfoCamera() {
}

void InfoCamera::init(string name, string link, string file) {
    name_camera = name;
    link_camera = link;
    link_dir = file;
}

Mat InfoCamera::getData() {
    if(flag_data_ready) {
        flag_data_ready = false;
        return m_buffer.clone();
    } else {
        return Mat();
    }
}

void InfoCamera::setData(Mat& data) {
    m_buffer = data.clone();
    flag_data_ready = true;
}