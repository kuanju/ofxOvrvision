//
//  ofxOvrvisionPro.cpp
//  ofxOvrvision
//
//  Created by kjwu on 1/7/16.
//
//

#include "ofxOvrvisionPro.h"

ofxOvrvisionPro::ofxOvrvisionPro(){
}

ofxOvrvisionPro::~ofxOvrvisionPro(){
    if(g_pOvrvision->isOpen()){
        cout<<"is open, close it first"<<endl;
        g_pOvrvision->Close();
    }
}

void ofxOvrvisionPro::init(){
    int locationID = 0;

    OVR::Camprop cameraMode = OVR::OV_CAMVR_FULL; //kj:1280x960 @45fps x2 ?
    ofSleepMillis(100); //wait for 1/10 sec kj: be conservative.
    
    ofSetVerticalSync(true);
    
    
    //Create Ovrvision object
    g_pOvrvision = new OVR::OvrvisionPro();
    
    if(g_pOvrvision->isOpen()){
        cout<<"is open, close it first"<<endl;
        g_pOvrvision->Close();
    }
    
    
//    g_pOvrvision->Open(locationID, cameraMode); //960x950 @60fps by default
    g_pOvrvision->Open(locationID, OVR::OV_CAMVR_FULL); //960x950 @60fps by default

    ofSleepMillis(100); //wait for 1/10 sec kj:be conservative.
    
    if (g_pOvrvision->isOpen() == false) {
        printf("Ovrvision Pro Open Error!\nPlease check whether OvrvisionPro is connected.");
    }
    
    //g_pOvrvision->SetCameraExposure(12960);
    g_pOvrvision->SetCameraSyncMode(false); //kj: white balance?
    
    //OculusRightGap
    g_hmdGap.x = g_pOvrvision->GetHMDRightGap(0) * -0.01f;
    g_hmdGap.y = g_pOvrvision->GetHMDRightGap(1) * 0.01f;
    g_hmdGap.z = g_pOvrvision->GetHMDRightGap(2) * 0.01f;
    
    g_camWidth = g_pOvrvision->GetCamWidth();
    g_camHeight = g_pOvrvision->GetCamHeight();
    
    cout<<"Ovrvision Camera size: "<<g_camWidth<< "x"<<g_camHeight<<endl;
    cout<<"buffer size of the Ovrvision image:"<<g_pOvrvision->GetCamBuffersize()<<endl;
    
    g_screen_texture.allocate(g_camWidth, g_camHeight,GL_RGBA);
    fbo.allocate(g_camWidth*2, g_camHeight, GL_RGBA);
    
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();

}

void ofxOvrvisionPro::update(){
    
    if (g_pOvrvision->isOpen())
    {
        //Full Draw
        g_pOvrvision->PreStoreCamData(g_processMode);
        //This function gets data from OvrvisionPro inside.
        
        p = g_pOvrvision->GetCamImageBGRA(OVR::OV_CAMEYE_LEFT);
        p2 = g_pOvrvision->GetCamImageBGRA(OVR::OV_CAMEYE_RIGHT);
        
        //        unsigned char* p = g_pOvrvision->GetCamImageBGRA(OVR::OV_CAMEYE_LEFT);
        //        unsigned char* p2 = g_pOvrvision->GetCamImageBGRA(OVR::OV_CAMEYE_RIGHT);
        
        
        /*get eyes view individually*/
        
        fbo.begin();
        g_screen_texture.loadData(p, g_camWidth, g_camHeight, GL_BGRA);
        
                g_screen_texture.draw(0,0);        //<- this is causing memory increase
        
//        fbo.attachTexture(g_screen_texture, GL_BGRA, 0);
        
        g_screen_texture.loadData(p2, g_camWidth, g_camHeight, GL_BGRA);
        
        g_screen_texture.draw(g_camWidth,0); //<- this is causing memory increase

        
        fbo.end();
        
    }

}

void ofxOvrvisionPro::draw(int _x =0, int _y =0){
    if (g_pOvrvision->isOpen())
    {
        fbo.draw(_x, _y);
        
        
    }

}

void ofxOvrvisionPro::exit(){
    g_pOvrvision->Close();
    
    //Delete object
    delete g_pOvrvision;

}

