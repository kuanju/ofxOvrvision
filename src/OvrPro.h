//
//  OvrPro.h
//
//  Created by kjwu on 1/7/16.
//
//

#pragma once
#include "ofMain.h"
#include <ovrvision_pro.h>


class OvrPro{
private:
    
public:
    OvrPro();
    ~OvrPro();
    
    void init();
    void update();
    void draw(int x, int y);
    void exit();
    
    //ovrvision pro related:
    int ovr_camWidth;
    int ovr_camHeight;
    
    OVR::Camprop cameraMode;
    OVR::Camqt ovr_processMode = OVR::Camqt::OV_CAMQT_DMS; //OV_CAMQT_DMSRMP, OV_CAMQT_DMS
    
    //regular renderer
    unsigned char * pixL;
    unsigned char * pixR;
    
    ofTexture texL;
    ofTexture texR;
    
    //method
    ofTexture getTextureLeft();
    ofTexture getTextureRight();

    
    /********* Future Todo: **********/

    //ofVec3f ovr_hmdGap;

    //buffer object renderer, OpenGL 4.5?
    //bool usePbo;
    //https://forum.openframeworks.cc/t/ofbufferobject-and-async-camera-video-texture-upload/21824
    //ofBufferObject pboL;
    //ofBufferObject pboR;

    
private:
    //buffer object renderer, OpenGL 4.5?
    //ofThreadChannel<unsigned char*> channelL;
    //ofThreadChannel<unsigned char*> channelR;
    //ofThreadChannel<bool> channelLReady;
    //ofThreadChannel<bool> channelRReady;
    
    
    //use smart pointer to let the c++ handle resource management.
    //std::unique_ptr<OVR::OvrvisionPro> ovr_Ovrvision;
    
    //use regular pointer: need to use with delet
    //OVR::OvrvisionPro* ovr_Ovrvision;
    
    //don't use pointer
    OVR::OvrvisionPro ovr_Ovrvision;
    
    
};