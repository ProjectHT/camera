/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Thong_Laptop
 *
 * Created on June 22, 2018, 10:39 AM
 */

#include <cstdlib>


#include "Vision/Camera.h"
#include "Vision/InfoCamera.h"
#include "Vision/Vision.h"
#include "Vision/InfoVision.h"

using namespace std;

/*
 * 
 */

static void* cameraThread(void* parameter) {
    InfoCamera* p_info = (InfoCamera*)parameter;
    Camera m_camera(p_info);
    m_camera.initSystem();
    if(!m_camera.run()) {
        cout << "|| Error camera ||" << endl;
    }
    pthread_exit(0);
}

static void* visionThread(void* parameter) {
    InfoVision* p_info = (InfoVision*)parameter;
    Vision m_vision(p_info);
    m_vision.run();
    //m_camera.initSystem();
    //if(!m_camera.run()) {
    //    cout << "|| Error camera ||" << endl;
    //}
    pthread_exit(0);
}

int main(int argc, char** argv) {
    InfoCamera listCamera[2];
    InfoVision listVision[2];
    
    listCamera[0] = InfoCamera();
    listCamera[0].init("1", "rtsp://admin:HIKdatviet@192.168.0.5:554/Streaming/Channels/101", "/var/www/html/camera");
    listVision[0] = InfoVision();
    listVision[0].init(&listCamera[0],"/var/www/html/log");
    listVision[0].flag_detect_person = true;
    listVision[0].flag_detect_face = false;
    pthread_t m_thread_1;
    int pid_1 = pthread_create(&m_thread_1, NULL, cameraThread, &(listCamera[0]));
    sleep(5);
    pthread_t m_thread_2;
    int pid_2 = pthread_create(&m_thread_2, NULL, visionThread, &(listVision[0]));
    sleep(5);
    listCamera[1] = InfoCamera();
    listCamera[1].init("2", "rtsp://admin:CPdatviet@192.168.0.6:554/cam/realmonitor?channel=1&subtype=0", "/var/www/html/camera");
    listVision[1] = InfoVision();
    listVision[1].init(&listCamera[1],"/var/www/html/log");
    listVision[1].flag_detect_person = false;
    listVision[1].flag_detect_face = true;
    pthread_t m_thread_3;
    int pid_3 = pthread_create(&m_thread_3, NULL, cameraThread,  &(listCamera[1]));
    sleep(5);
    pthread_t m_thread_4;
    int pid_4 = pthread_create(&m_thread_4, NULL, visionThread,  &(listVision[1]));
    
    long loop = 0;
    while(loop < 100000000000) {
        sleep(1);
        loop++;
    }
    listCamera[0].flag_run = false;
    listVision[0].flag_run = false;
    listCamera[1].flag_run = false;
    listVision[1].flag_run = false;
    sleep(1);
    
    return 0;
}

