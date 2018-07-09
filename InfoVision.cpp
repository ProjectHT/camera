/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InfoVision.cpp
 * Author: phamh
 * 
 * Created on June 27, 2018, 11:19 AM
 */

#include "InfoVision.h"

InfoVision::InfoVision() {
}

InfoVision::InfoVision(const InfoVision& orig) {
    p_info_camera = orig.p_info_camera;
    link_log = orig.link_log;
}

InfoVision::~InfoVision() {
}

void InfoVision::init(InfoCamera* info_camera, string log) {
    p_info_camera = info_camera;
    link_log = log;
}