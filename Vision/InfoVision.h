/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InfoVision.h
 * Author: phamh
 *
 * Created on June 27, 2018, 11:19 AM
 */

#ifndef INFOVISION_H
#define INFOVISION_H

#include <iostream>
#include <string.h>
#include "InfoCamera.h"

using namespace std;

class InfoVision {
public:
    InfoVision();
    InfoVision(const InfoVision& orig);
    virtual ~InfoVision();
    
    void init(InfoCamera* info_camera, string log);
    bool flag_detect_person;
    bool flag_detect_face;
    bool flag_run;
    InfoCamera *p_info_camera;
    string link_log;
private:
    
};

#endif /* INFOVISION_H */

