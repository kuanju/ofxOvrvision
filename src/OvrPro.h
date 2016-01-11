//
//  ofxOvrvisionPro.h
//  ofxOvrvision
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
        ofFbo fbo;
        ofTexture ovr_screen_texture;

        //buffer object renderer, OpenGL 4.5? 
        bool usePbo;
        //https://forum.openframeworks.cc/t/ofbufferobject-and-async-camera-video-texture-upload/21824
        ofTexture tex;
        ofBufferObject pbo;
        ofThreadChannel<unsigned char*> channel;
        ofThreadChannel<bool> channelReady;

    
        //use smart pointer to let the c++ handle resource management.
        std::unique_ptr<OVR::OvrvisionPro> ovr_Ovrvision;
    
        //use regular pointer: need to use with delet
        //        OVR::OvrvisionPro* ovr_Ovrvision;


};