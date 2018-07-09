/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camera.h
 * Author: Thong_Laptop
 *
 * Created on June 22, 2018, 10:51 AM
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "InfoCamera.h"
#include "Clip.h"
#include "../Http/HTTPRequest.h"
#include "Clip.h"
#include <ctime>
#include <locale>
#include <sys/time.h>
#include <pthread.h>
#include <opencv/cv.hpp>
#include <opencv2/opencv.hpp>

extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavformat/avio.h>
    #include <libswscale/swscale.h>
}

using namespace std;
using namespace cv;

class Camera {
public:
    Camera(InfoCamera* p_info);
    Camera(const Camera& orig);
    virtual ~Camera();
    
    void initSystem();
    bool run();
    
private:
    InfoCamera* p_info_camera;
    
    unsigned long count = 0;
    
    long index_first_frame;
    
    int getMs();
    
    string getDayTime();
    
    bool initCamera(AVFormatContext** inputFormatContext, int& index_stream, AVCodecContext** inputCodec);
    
    bool initSaveFile(AVFormatContext** outputFormatContext, AVOutputFormat** outputFormat);
    bool tranferCodec(AVFormatContext* inputFormatContext, AVFormatContext* outFormatContext, int& index_stream);
    bool createFile(AVFormatContext* outFormatContext);
    bool writeHeaderFile(AVFormatContext* outFormatContext);
    void writeFile(AVFormatContext* outFormatContext, AVPacket* data);
    void closeFile(AVFormatContext* outFormatContext);
    
    bool createNewFile(AVFormatContext* inputFormatContext, AVFormatContext** outputFormatContext, int& index_stream);

    void initConvertToImage(SwsContext** img_convert, uint8_t** input, uint8_t** ouput, AVCodecContext* codec, AVFrame** frameYUV, AVFrame** frameBGR);
    Mat convertToImage(SwsContext* img_convert, AVPacket* data, AVCodecContext* codec, AVFrame* frameYUV, AVFrame* frameBGR);
    void compressionParamsImage(vector<int>& compression_params);
    void saveImage(Mat& src, vector<int>& compression_params,int& flag);
    
    void haveFrame (Mat & src, Clip** clip, int & index_per_second, vector<int> & compression_params_frame);
};

#endif /* CAMERA_H */

