/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camera.cpp
 * Author: Thong_Laptop
 * 
 * Created on June 22, 2018, 10:51 AM
 */

#include "Camera.h"

static void* sendData(void* parameter) {
    cout << "send" << endl;
    string* param = (string*)parameter;
    HTTPRequest temp;
    string host = param[0];
    string link = param[1];
    string data = param[2];
    cout << param[2] << endl;
    temp.post(host,link,80,data);
    pthread_exit(0);
}

Camera::Camera(InfoCamera* p_info) {
    p_info_camera = p_info;
}

Camera::Camera(const Camera& orig) {
    this->p_info_camera = orig.p_info_camera;
}

Camera::~Camera() {
}

int Camera::getMs() {    
    timeval tp;
    gettimeofday(&tp, 0);
    //time_t curtime = tp.tv_sec;
    //tm *t = localtime(&curtime);
    return (tp.tv_usec/1000);
}

string Camera::getDayTime() {
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

void Camera::initSystem() {
    av_register_all();
    avcodec_register_all();
    avformat_network_init();
}

bool Camera::initCamera(AVFormatContext** inputFormatContext, int& index_stream, AVCodecContext** inputCodec) {
    if (avformat_open_input(inputFormatContext, p_info_camera->link_camera.c_str(), NULL, NULL)!=0) {
        printf("|Camera| : Couldn't open input!\n");
        return false;
    }
    
    if (avformat_find_stream_info(*inputFormatContext, NULL)<0) {
        printf("|Camera| : Couldn't find stream information!\n");
        return false;
    }
    
    av_dump_format(*inputFormatContext, 0, p_info_camera->link_camera.c_str(), 0);
    
    index_stream = -1;
    for(int i= 0; i < (*inputFormatContext)->nb_streams; i++) {
        if((*inputFormatContext)->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            index_stream = i;
            break;
        }
    }
    
    if(index_stream == -1) {
        printf("|Camera| : Didn't find a video stream!\n");
        return false;
    }
    
    //av_read_play((*inputFormatContext));
    
    *inputCodec = (*inputFormatContext)->streams[index_stream]->codec;
    AVCodec * pCodec = avcodec_find_decoder((*inputCodec)->codec_id);
    if(pCodec == NULL) {
        printf("|Camera| : Didn't find codec!\n");
        return false;
    }
    
    if(avcodec_open2(*inputCodec, pCodec, NULL) < 0) {
        printf("|Camera| : Didn't load codec!\n");
        return false;
    }
    return true;
}

bool Camera::initSaveFile(AVFormatContext** outputFormatContext, AVOutputFormat** outputFormat) {
    if ((*outputFormat = av_guess_format(NULL, "mp4", "video/mp4")) == NULL) {
        printf("|Camera| : Failed to define output format!\n");
        return false;
    }
    
    avformat_alloc_output_context2(outputFormatContext, av_guess_format("mp4", NULL, "video/mp4"), NULL, NULL);
    if (*outputFormatContext == NULL) {
        printf("|Camera| : Couldn't create output!\n");
        return false;
    }
    return true;
}

bool Camera::tranferCodec(AVFormatContext* inputFormatContext, AVFormatContext* outFormatContext, int& index_stream) {
    AVStream* inAVStream = inputFormatContext->streams[index_stream];
    AVStream* outAVStream = avformat_new_stream(outFormatContext, inAVStream->codec->codec);

    if (avcodec_copy_context(outAVStream->codec, inAVStream->codec) < 0) {
        return false;
    } else {
        outAVStream->codec->codec_tag = 0;
        if (outFormatContext->oformat->flags & AVFMT_GLOBALHEADER) {
            outAVStream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
        }
        outAVStream->duration = 108000;
        outAVStream->pts.num = 0;
        outAVStream->pts.val = 0;
        return true;
    }
}

bool Camera::createFile(AVFormatContext* outFormatContext) {
    string link_file = p_info_camera->link_dir + "/" + p_info_camera->name_camera + "_" + getDayTime() + ".mp4";
    avio_open(&outFormatContext->pb, link_file.c_str(), AVIO_FLAG_READ_WRITE);
    if(outFormatContext->pb == NULL) {
        return false;
    } else {
        return true;
    }
}

bool Camera::writeHeaderFile(AVFormatContext* outFormatContext) {
    if (avformat_write_header(outFormatContext, NULL) != 0) {
        return false;
    } else {
        return true;
    }
}

void Camera::writeFile(AVFormatContext* outFormatContext, AVPacket* data) {
    av_write_frame(outFormatContext, data);
}

void Camera::closeFile(AVFormatContext* outFormatContext) {
    avio_close(outFormatContext->pb);
}

bool Camera::createNewFile(AVFormatContext* inputFormatContext, AVFormatContext** outputFormatContext, int& index_stream) {
    AVOutputFormat* pOutputFormat;
    
    if(initSaveFile(outputFormatContext, &pOutputFormat) == false) {
        printf("|Camera| : init save error!\n");
        return false;
    } else {
        printf("|Camera| : init save successful!\n");
    }
    
    if(tranferCodec(inputFormatContext, *outputFormatContext, index_stream) == false) {
        printf("|Camera| : Failed to copy codec context!\n");
        return false;
    }
    
    if(createFile(*outputFormatContext) == false) {
        printf("|Camera| : Could not open for writing!\n");
        return false;
    }
    
    if(writeHeaderFile(*outputFormatContext) == false) {
        printf("|Camera| : Could not write header!\n");
        return false;
    } 
    
    return true;
}

void Camera::initConvertToImage(SwsContext** img_convert, uint8_t** input, uint8_t** ouput, AVCodecContext* codec, AVFrame** frameYUV, AVFrame** frameBGR) {
    *img_convert = sws_getContext(codec->width, codec->height, codec->pix_fmt, codec->width, codec->height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);
    int size1 = avpicture_get_size(AV_PIX_FMT_YUV420P, codec->width, codec->height);
    int size2 = avpicture_get_size(AV_PIX_FMT_BGR24, codec->width, codec->height);
    *input = (uint8_t*) (av_malloc(size1));
    *ouput = (uint8_t*) (av_malloc(size2));
    *frameYUV = av_frame_alloc();
    *frameBGR = av_frame_alloc();
    avpicture_fill((AVPicture *) *frameYUV, *input, AV_PIX_FMT_YUV420P, codec->width, codec->height);
    avpicture_fill((AVPicture *) *frameBGR, *ouput, AV_PIX_FMT_BGR24, codec->width, codec->height);
}

Mat Camera::convertToImage(SwsContext* img_convert, AVPacket* data, AVCodecContext* codec, AVFrame* frameYUV, AVFrame* frameBGR) {
    int check = 0;
    int temp = avcodec_decode_video2(codec, frameYUV, &check, data);
    //cout << temp << endl;
    if( temp > 0) {
        sws_scale(img_convert, frameYUV->data, frameYUV->linesize, 0, codec->height, frameBGR->data, frameBGR->linesize);
        return Mat(codec->height, codec->width, CV_8UC3, frameBGR->data[0], frameBGR->linesize[0]);
    } else {
        return Mat();
    }
}

void Camera::compressionParamsImage(vector<int>& compression_params) {
    compression_params.push_back( cv::IMWRITE_JPEG_QUALITY );
    compression_params.push_back( 70 );
}

void Camera::saveImage(Mat& src, vector<int>& compression_params,int& flag) {
    int index = getMs() / 100;
    if(flag != index) {
        flag = index;
        string path = p_info_camera->link_dir + "/camera" + p_info_camera->name_camera + "_" + std::to_string(index) + ".jpg";
        imwrite(path.c_str(), src, compression_params);
    }   
}

bool Camera::run() {
    AVFormatContext *pFormatCtx = NULL;
    int index_video_stream;
    AVCodecContext *pCodecCtx = NULL;
    
    if(initCamera(&pFormatCtx, index_video_stream, &pCodecCtx) == false) {
        printf("|Camera| : init input error!\n");
        return false;
    } else {
        printf("|Camera| : init input successful!\n");
    }
    
    SwsContext *img_convert_ctx = NULL;
    uint8_t* buffer_in = NULL;
    uint8_t* buffer_out = NULL;
    AVFrame* picture_yuv = NULL;
    AVFrame* picture_rgb = NULL;
    initConvertToImage(&img_convert_ctx, &buffer_in, &buffer_out, pCodecCtx, &picture_yuv, &picture_rgb);
    p_info_camera->flag_run = true;
    long count = 0;
    long index = 0;
    int flag_write = -1;
    
    vector<int> compression_params;
    compressionParamsImage(compression_params);
    
    AVFormatContext* pOutFormatContext;
    
    int count_no_obj = 0;
    bool flag_have_obj;
    
    Clip* m_clip = NULL;
    
    while(p_info_camera->flag_run) {
        AVPacket packet;
        av_init_packet(&packet);
        if(av_read_frame(pFormatCtx, &packet) >= 0) {
            if (packet.stream_index == index_video_stream) {
                if(count < 108000) {
                    if(count == 0) {
                        pOutFormatContext = NULL;
                        if(createNewFile(pFormatCtx, &pOutFormatContext, index_video_stream) == false) {
                            //printf("|Camera| : create file[%d] error!\n", index_file);
                            av_free_packet(&packet);
                            break;
                        }
                        index = packet.dts;
                        Mat m_mat = convertToImage(img_convert_ctx, &packet, pCodecCtx, picture_yuv, picture_rgb);
                        if(!m_mat.empty()) {
                            haveFrame(m_mat, (&m_clip), flag_write, compression_params);
                        }
                        packet.dts = 0;
                        count++;
                        writeFile(pOutFormatContext, &packet);
                        
                    } else {
                        //if(index <  packet.dts) {
                            index = packet.dts;
                            Mat m_mat = convertToImage(img_convert_ctx, &packet, pCodecCtx, picture_yuv, picture_rgb);
                            if(!m_mat.empty()) {
                                haveFrame(m_mat, (&m_clip), flag_write, compression_params);
                            }
                            packet.dts = count;
                            count++;
                            writeFile(pOutFormatContext, &packet);
                            
                        //}
                    }
                } else {
                    avio_close(pOutFormatContext->pb);
                    avformat_free_context(pOutFormatContext);
                    pOutFormatContext = NULL;
                    if(createNewFile(pFormatCtx, &pOutFormatContext, index_video_stream) == false) {
                        //printf("|Camera| : create file[%d] error!\n", index_file);
                        av_free_packet(&packet);
                        break;
                    }
                    index = packet.dts;
                    Mat m_mat = convertToImage(img_convert_ctx, &packet, pCodecCtx, picture_yuv, picture_rgb);
                    if(!m_mat.empty()) {
                        haveFrame(m_mat, (&m_clip), flag_write, compression_params);
                    }
                    packet.dts = 0;
                    count = 0;
                    writeFile(pOutFormatContext, &packet);
                }
            }
            //av_free_packet(&packet);
        }
    }
    av_free(picture_yuv);
    av_free(picture_rgb);
    av_free(buffer_in);
    av_free(buffer_out);
    av_read_pause(pFormatCtx);
    if(p_info_camera->flag_run) {
        avio_close(pOutFormatContext->pb);
        avformat_free_context(pOutFormatContext);
    }
}

void Camera::haveFrame (Mat & src, Clip** clip, int & index_per_second, vector<int> & compression_params_frame) {
    if(p_info_camera->flag_save) {
        if((*clip) == NULL) {
            (*clip) = new Clip(src.size());
            (*clip)->writeImage(src);
            (*clip)->putFrame(src);
            string data_send[3];
            data_send[0] = "pnj.smartlook.asia";
            data_send[1] = "/api/input_image.php";
            data_send[2] = "session=" + (*clip)->getNameFile() + "&id_camera=" + p_info_camera->name_camera + "&url_image=http://lab.jtechgroup.co/Clip/"+ (*clip)->getNameFile()+".jpg";
            pthread_t temp_thread;
            int pid = pthread_create(&temp_thread, NULL, sendData, &(data_send));
            usleep(1000);
        } else {
            (*clip)->putFrame(src);
            usleep(5000);
        } 
    } else {
        if((*clip) != NULL) {
            (*clip)->stop();
            string data_send[3];
            data_send[0] = "pnj.smartlook.asia";
            data_send[1] = "/api/input_video.php";
            data_send[2] = "session=" + (*clip)->getNameFile() + "&id_camera=" + p_info_camera->name_camera + "&url_video=http://lab.jtechgroup.co/Clip/"+ (*clip)->getNameFile()+".avi";
            pthread_t temp_thread;
            int pid = pthread_create(&temp_thread, NULL, sendData, &(data_send));
            usleep(1000);
            delete (*clip);
            (*clip) = NULL;
        }
    }
    
    /*if(p_info_camera->flag_save) {
        count_down_frame_save
        if((*clip) == NULL) {
            if(count_down_frame_save < 30) {
                count_down_frame_save++;
            } else {
                (*clip) = new Clip(src.size());
                (*clip)->writeImage(src);
                (*clip)->putFrame(src);
                string data_send[3];
                data_send[0] = "pnj.smartlook.asia";
                data_send[1] = "/api/input_image.php";
                data_send[2] = "session=" + (*clip)->getNameFile() + "&id_camera=" + p_info_camera->name_camera + "&url_image=http://lab.jtechgroup.co/Clip/"+ (*clip)->getNameFile()+".jpg";
                pthread_t temp_thread;
                int pid = pthread_create(&temp_thread, NULL, sendData, &(data_send));
                usleep(1000);
            }
        } else {
            count_down_frame_save = 300;
            (*clip)->putFrame(src);
            usleep(1000);
        }
    } else {
        if((*clip) != NULL) {
            if(count_down_frame_save != 0) {
                count_down_frame_save--;
                (*clip)->putFrame(src);
                usleep(1000);
            } else {
                (*clip)->stop();
                string data_send[3];
                data_send[0] = "pnj.smartlook.asia";
                data_send[1] = "/api/input_video.php";
                data_send[2] = "session=" + (*clip)->getNameFile() + "&id_camera=" + p_info_camera->name_camera + "&url_video=http://lab.jtechgroup.co/Clip/"+ (*clip)->getNameFile()+".avi";
                pthread_t temp_thread;
                int pid = pthread_create(&temp_thread, NULL, sendData, &(data_send));
                usleep(1000);
                delete (*clip);
                (*clip) = NULL;
            }
        }   
    }*/
    Mat m_mat_for_show;
    resize(src, m_mat_for_show, Size(), 0.5, 0.5, INTER_CUBIC);
    saveImage(m_mat_for_show, compression_params_frame, index_per_second);
    p_info_camera->setData(src);
    src.release();
}