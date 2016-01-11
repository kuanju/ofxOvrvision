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
    
        void init();
        void update();
        void draw(int x, int y);
        void exit();
    
        //ovrvision pro related:
    
        int ovr_camWidth;
        int ovr_camHeight;

        ofVec3f ovr_hmdGap;

    
//        OVR::OvrvisionPro* ovr_Ovrvision;
    
        OVR::Camprop cameraMode;
        OVR::Camqt ovr_processMode = OVR::Camqt::OV_CAMQT_DMS;
    
//        unsigned char* p;
//        unsigned char* p2;

        //renderer
        ofFbo fbo;
        ofTexture ovr_screen_texture;
        ofPixels ovr_screen_pixel;
        //try using buffer object as PBO (Pixel Buffer Object)
        ofBufferObject pixelBuffer;

        //https://forum.openframeworks.cc/t/ofbufferobject-and-async-camera-video-texture-upload/21824
        ofTexture tex;
        ofBufferObject pbo1;
        ofThreadChannel<unsigned char*> channel;
        ofThreadChannel<bool> channelReady;

    
        //use smart point to let the c++ handle resource management.
        std::unique_ptr<OVR::OvrvisionPro> ovr_Ovrvision;

};