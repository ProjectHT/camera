/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vision.cpp
 * Author: phamh
 * 
 * Created on June 27, 2018, 10:21 AM
 */

#include "Vision.h"
static void* sendData(void* parameter) {
    cout << "send" << endl;
    string* param = (string*)parameter;
    HTTPRequest temp;
    string host = param[0];
    string link = param[1];
    string data = param[2];
    cout << param[2] << endl;
    temp.post(host,link,80,data);
    //detete param[0];
    pthread_exit(0);
}


Vision::Vision(InfoVision* info) {
    this->p_info_vision = info;
}

Vision::Vision(const Vision& orig) {
    this->p_info_vision = orig.p_info_vision;
    this->hog_detect_person = orig.hog_detect_person;
}

Vision::~Vision() {
}

void Vision::initDetectPerson() {
    hog_detect_person.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
}

void Vision::dectectPerson(Mat &input, vector<Rect> &area, int &offset_x, int &offset_y) {
    vector<Rect> found;
    area.clear();
    timeval tp_begin, tp_end;
    gettimeofday(&tp_begin, 0);
    //GaussianBlur(input, input, Size(3, 3), 1.4, 0, 4);
    hog_detect_person.detectMultiScale(input, found, 0, Size(4, 4), Size(16, 16), 1.1, 3);
    gettimeofday(&tp_end, 0);
    double time_loop = measureTime(tp_begin, tp_end);
    //printf("|Vision| - Detect person - time : %2.3lf s\n",time_loop);
    size_t i, j;
    for (i = 0; i<found.size(); i++)
    {
        Rect r = found[i];
        for (j = 0; j<found.size(); j++)
                if (j != i && (r & found[j]) == r)
                        break;
        if (j == found.size())
                area.push_back(r);
    }

    for (i = 0; i<area.size(); i++)
    {
        area[i].x += offset_x;
        area[i].y += offset_y;
    }
}

double Vision::measureTime(timeval& begin, timeval& end) {
    long time; 
    time = (end.tv_sec - begin.tv_sec)*1000000 + (end.tv_usec - begin.tv_usec);
    return ((double)time)*0.0000001;
}

Mat Vision::morphologyOperations(Mat& in) {
    int operation = 3;
    int morph_elem = 0;
    int morph_size = 9;
    Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
    Mat temp_out;
    morphologyEx(in, temp_out, operation, element);
    //saveImage(temp_out,3,compression_params);
    operation = 2;
    morph_elem = 0;
    morph_size = 3;
    Mat out;
    element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
    morphologyEx(temp_out, out, operation, element);
    //saveImage(out,4,compression_params);
    return out;
}

void Vision::createBackground() {
    if (background.cols == 0) {
        background = Mat(input.size(), CV_32FC1);
        input.convertTo(background, CV_32FC1);
    }
    else {
        size_t m_loop = input.cols * input.rows;
        float *p_data_background = (float*)background.data;
        unsigned char *p_data_input = (unsigned char*)input.data;
        for (size_t i = 0; i < m_loop; i++) {
            float temp;
            temp = 0.8*p_data_background[i] + 0.2f*((float)p_data_input[i]);
            p_data_background[i] = temp;
        }
    }
}

bool Vision::detectObj() {
    Mat temp_sub_background = Mat(input.size(), CV_8UC1);
    size_t m_loop = input.cols * input.rows;
    float *p_data_background = (float*)background.data;
    unsigned char *p_data_input = (unsigned char*)input.data;
    unsigned char *p_temp_sub_background = (unsigned char*)temp_sub_background.data;
    for (size_t i = 0; i < m_loop; i++) {
        unsigned char temp;
        if ((float)p_data_input[i] > (p_data_background[i]*1.15f)) {
            p_temp_sub_background[i] = 255;
            float temp;
            temp = 0.98f*p_data_background[i] + 0.02f*((float)p_data_input[i]);
            p_data_background[i] = temp;
        }
        else if ((float)p_data_input[i] < (p_data_background[i]*0.85f)) {
            p_temp_sub_background[i] = 255;
            float temp;
            temp = 0.98f*p_data_background[i] + 0.02f*((float)p_data_input[i]);
            p_data_background[i] = temp;
        }
        else {
            p_temp_sub_background[i] = 0;
            float temp;
            temp = 0.9f*p_data_background[i] + 0.1f*((float)p_data_input[i]);
            p_data_background[i] = temp;
        }
    }
    //saveImage(background,0,compression_params);
    
    Mat temp_buffer_1 = morphologyOperations(temp_sub_background);
    Mat temp_buffer_2;
    GaussianBlur(temp_buffer_1, temp_buffer_2, Size(5, 5), 1.4, 0, 4);
    Mat temp_buffer_3;
    Canny(temp_buffer_2, temp_buffer_3, 5, 20, 3, false);
    
    
    saveImage(temp_buffer_3,2,compression_params);
    //saveImage(temp_sub_background,2,compression_params);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(temp_buffer_3, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));
    vector<Rect> area_step_1;
    Scalar color = Scalar(0);
    for (int i = 0; i < contours.size(); i++) {
        Rect temp_rect = boundingRect(contours[i]);
        //if ((temp_rect.width +  temp_rect.x > temp_buffer_3.cols - 10) ||(temp_rect.height+  temp_rect.y > temp_buffer_3.rows - 10) || (temp_rect.height < 40) || (temp_rect.width < 25) || (temp_rect.x < 10) || ((temp_rect.y < 10))) {
        //    continue;
        //}
        if((temp_rect.height < 80) || (temp_rect.width < 40)) {
            continue;
        }
        area_step_1.push_back(temp_rect);
    }
    if(area_step_1.size() < 1) {
        //saveImage(input,1,compression_params);
        Mat temp;
        resize(src, temp, Size(),0.25,0.25, INTER_CUBIC);
        //saveImage(temp,3,compression_params);
        return false;
    }
    vector<Rect> person;
    for(int i = 0; i < area_step_1.size(); i++) {
        rectangle(input, area_step_1.at(i), Scalar(255), 1, 8, 0);
        area_step_1.at(i).x = 4*(area_step_1.at(i).x);
        area_step_1.at(i).y = 4*(area_step_1.at(i).y);
        area_step_1.at(i).width = 4*(area_step_1.at(i).width);
        area_step_1.at(i).height = 4*(area_step_1.at(i).height);
        int temp_1 = 0.2 * area_step_1.at(i).width; 
        int temp_2 = 0.2 * area_step_1.at(i).height; 
        if(area_step_1.at(i).x + area_step_1.at(i).width + temp_1 < src.cols) {
            area_step_1.at(i).width += temp_1; 
        } else {
            area_step_1.at(i).width = src.cols - area_step_1.at(i).x;
        }
        if(area_step_1.at(i).y + area_step_1.at(i).height + temp_2 < src.rows) {
            area_step_1.at(i).height += temp_2; 
        } else {
            area_step_1.at(i).height = src.rows - area_step_1.at(i).y;
        }
        if(area_step_1.at(i).x > temp_1) {
            area_step_1.at(i).width += temp_1;
            area_step_1.at(i).x -= temp_1;
        } else {
            area_step_1.at(i).width += area_step_1.at(i).x;
            area_step_1.at(i).x = 0;
        }
        if(area_step_1.at(i).y > temp_2) {
            area_step_1.at(i).height += temp_2;
            area_step_1.at(i).y -= temp_2;
        } else {
            area_step_1.at(i).height += area_step_1.at(i).y;
            area_step_1.at(i).y = 0;
        }
        Mat temp_buffer_4 = src(area_step_1.at(i));
        vector<Rect> temp_person;
        dectectPerson(temp_buffer_4, temp_person, area_step_1.at(i).x, area_step_1.at(i).y);
        if(temp_person.size()> 0) {
            person.assign(temp_person.begin(),temp_person.end());
        }
    }
    //saveImage(input,1,compression_params);
    if(area_step_1.size() < 0) {
        //Mat temp;
        //resize(src, temp, Size(),0.25,0.25, INTER_CUBIC);
        //saveImage(temp,3,compression_params);
        return false;
    }
    return true;
    //cout << "pesron : " << area_step_1.size() << endl;
    //for(int i = 0; i < area_step_1.size(); i++) {
    //    rectangle(src, area_step_1.at(i), Scalar(255), 8, 8, 0);
    //}
    
    //Mat temp;
    //resize(src, temp, Size(),0.25,0.25, INTER_CUBIC);
    //saveImage(temp,3,compression_params);
}

void Vision::loadInput() {
    while(1) {
        display = p_info_vision->p_info_camera->getData();
        if(!display.empty()) {
            cvtColor(display,src,CV_BGR2GRAY);
            resize(src, input, Size(), 0.25, 0.25, INTER_CUBIC);
            GaussianBlur(input, input, Size(5, 5), 1.4, 0, 4);
            //cout << "input size : " <<  input.cols << "x" << input.rows << endl;
            break;
        }
        usleep (10000);
    }
}

void Vision::run() {
    p_info_vision->flag_run = true;
    initDetectPerson();
    long count = 0;
    loadInput();
    VideoWriter video_debug;
    //vector<int> compression_params;
    compressionParamsImage(compression_params);
    bool flag_obj = false;
    long count_1_detect_obj = 0;
    long count_2_detect_obj = 0;
    Clip* m_clip = NULL;
    while(p_info_vision->flag_run) {
        loadInput();
        count++;
        if(count < 300) {
            createBackground();
            if(count == 280) {
                video_debug.open("/home/smartsys/my_debug_10.avi",CV_FOURCC('H', '2', '6', '4'),10, background.size(),true);
            }
        } else {
            if(detectObj()) {
                count_1_detect_obj++;
                if(count_1_detect_obj > 10) {
                    count_2_detect_obj = 0;
                    flag_obj = true;
                }
            } else {
                count_2_detect_obj++;
                if(count_2_detect_obj > 150) {
                    count_1_detect_obj = 0;
                    flag_obj = false;
                    if(m_clip != NULL) {
                        m_clip->stop();
                        string data_send[3];
                        data_send[0] = "pnj.smartlook.asia";
                        data_send[1] = "/api/input_video.php";
                        data_send[2] = "session=" + m_clip->getNameFile() + "&id_camera=1" + "&url_video=http://lab.jtechgroup.co/Clip/"+m_clip->getNameFile()+".avi";
                        pthread_t temp_thread;
                        int pid = pthread_create(&temp_thread, NULL, sendData, &(data_send));
                        usleep(1000);
                        delete m_clip;
                        m_clip = NULL;
                    }
                }
            }
            
            if(flag_obj) {
                if(m_clip == NULL) {
                    m_clip = new Clip(display.size());
                    m_clip->putFrame(display);
                    string data_send[3];
                    data_send[0] = "pnj.smartlook.asia";
                    data_send[1] = "/api/input_image.php";
                    data_send[2] = "session=" + m_clip->getNameFile() + "&id_camera=1" + "&url_image=http://lab.jtechgroup.co/Clip/"+m_clip->getNameFile()+".jpg";
                    pthread_t temp_thread;
                    int pid = pthread_create(&temp_thread, NULL, sendData, &(data_send));
                    usleep(1000);
                }
                cout << "Co nguoi" << endl;
                m_clip->writeImage(display);
            }
            video_debug.write(display);
        }
        
    }
    video_debug.release();
}

void Vision::compressionParamsImage(vector<int>& compression_params) {
    compression_params.push_back( CV_IMWRITE_JPEG_QUALITY );
    compression_params.push_back( 70 );
}

void Vision::saveImage(Mat& input, int index,vector<int>& compression_params) {
    string path = p_info_vision->link_log + "/" + p_info_vision->p_info_camera->name_camera + "_" + std::to_string(index) + "_"+ std::to_string(getMs()/100) + ".jpg";
    imwrite(path.c_str(), input, compression_params); 
}

int Vision::getMs() {    
    timeval tp;
    gettimeofday(&tp, 0);
    return (tp.tv_usec/1000);
}