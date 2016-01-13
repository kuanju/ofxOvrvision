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
    
    void init(bool _usePbo);
    void update();
    void draw(int x, int y);
    void exit();
    
    //ovrvision pro related:
    
    int ovr_camWidth;
    int ovr_camHeight;
    
    ofVec3f ovr_hmdGap;
    
    
    OVR::Camprop cameraMode;
    OVR::Camqt ovr_processMode = OVR::Camqt::OV_CAMQT_DMS;
    
    //regular renderer
    ofFbo fboL;
    unsigned char * pixL;
    
    
    //buffer object renderer, OpenGL 4.5?
    bool usePbo;
    //https://forum.openframeworks.cc/t/ofbufferobject-and-async-camera-video-texture-upload/21824
    ofTexture texL;
    ofBufferObject pboL;
    ofThreadChannel<unsigned char*> channelL;
    ofThreadChannel<bool> channelLReady;
    
    
    //use smart pointer to let the c++ handle resource management.
    //    std::unique_ptr<OVR::OvrvisionPro> ovr_Ovrvision;
    
    //use regular pointer: need to use with delet
    //            OVR::OvrvisionPro* ovr_Ovrvision;
    
    OVR::OvrvisionPro ovr_Ovrvision;
    
    
};