/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HTTPRequest.h
 * Author: phamh
 *
 * Created on July 2, 2018, 12:14 PM
 */

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

class HTTPRequest {
public:
    HTTPRequest();
    HTTPRequest(const HTTPRequest& orig);
    virtual ~HTTPRequest();
    
    bool post(string host, string link, int port, string data);
private:
};

#endif /* HTTPREQUEST_H */

