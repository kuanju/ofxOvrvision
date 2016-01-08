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
    
        int g_camWidth;
        int g_camHeight;

        ofTexture g_screen_texture;
        ofVec3f g_hmdGap;
        
        OVR::OvrvisionPro* g_pOvrvision;
        OVR::Camqt g_processMode = OVR::Camqt::OV_CAMQT_DMS;
        
        unsigned char* p;
        unsigned char* p2;

        //renderer
        ofFbo fbo;

    private:
};