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


class ofxOvrvisionPro{
    public:
        ofxOvrvisionPro();
        ~ofxOvrvisionPro();
    
        void init();
        void update();
        void draw(int x, int y);
        void exit();
    
        //ovrvision pro related:
    
        int ovr_camWidth;
        int ovr_camHeight;

        ofTexture ovr_screen_texture;
        ofVec3f ovr_hmdGap;

    
        OVR::OvrvisionPro* ovr_Ovrvision;
        OVR::Camprop cameraMode;
        OVR::Camqt ovr_processMode = OVR::Camqt::OV_CAMQT_DMS;
    
        unsigned char* p;
        unsigned char* p2;

        //renderer
        ofFbo fbo;

    private:
};