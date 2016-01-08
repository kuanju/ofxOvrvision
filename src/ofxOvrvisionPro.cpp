//
//  ofxOvrvisionPro.cpp
//  ofxOvrvision
//
//  Created by kjwu on 1/7/16.
//
//

#include "ofxOvrvisionPro.h"

ofxOvrvisionPro::ofxOvrvisionPro(){
    cameraMode = OVR::OV_CAMVR_FULL; //kj:1280x960 @45fps x2 ?

    //Create Ovrvision object
    ovr_Ovrvision = new OVR::OvrvisionPro();
    ofSleepMillis(1000);

}

ofxOvrvisionPro::~ofxOvrvisionPro(){
    if(ovr_Ovrvision->isOpen()){
        cout<<"it's open, close it "<<endl;
        ovr_Ovrvision->Close();
    }
}

void ofxOvrvisionPro::init(){
    int locationID = 0;
    ofSetVerticalSync(true);
    
    
    if(ovr_Ovrvision->isOpen()){
        cout<<"it's open, close it"<<endl;
        ovr_Ovrvision->Close();
    }
    
    ovr_Ovrvision->Open(locationID, cameraMode); //960x950 @60fps by default

    ofSleepMillis(100); //wait for 1/10 sec kj:be conservative.
    
    if (ovr_Ovrvision->isOpen() == false) {
        printf("Ovrvision Pro Open Error!\nPlease check whether OvrvisionPro is connected.");
    }
    
    //ovr_Ovrvision->SetCameraExposure(12960);
    ovr_Ovrvision->SetCameraSyncMode(false); //kj: white balance?
    
    //OculusRightGap
    ovr_hmdGap.x = ovr_Ovrvision->GetHMDRightGap(0) * -0.01f;
    ovr_hmdGap.y = ovr_Ovrvision->GetHMDRightGap(1) * 0.01f;
    ovr_hmdGap.z = ovr_Ovrvision->GetHMDRightGap(2) * 0.01f;
    
    ovr_camWidth = ovr_Ovrvision->GetCamWidth();
    ovr_camHeight = ovr_Ovrvision->GetCamHeight();
    
    cout<<"Ovrvision Camera size: "<<ovr_camWidth<< "x"<<ovr_camHeight<<endl;
    cout<<"buffer size of the Ovrvision image:"<<ovr_Ovrvision->GetCamBuffersize()<<endl;
    
    ovr_screen_texture.allocate(ovr_camWidth, ovr_camHeight,GL_RGBA);
    fbo.allocate(ovr_camWidth*2, ovr_camHeight, GL_RGBA);
    
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();

}

void ofxOvrvisionPro::update(){
    
    if (ovr_Ovrvision->isOpen())
    {
        //Full Draw
        ovr_Ovrvision->PreStoreCamData(ovr_processMode);
        //This function gets data from OvrvisionPro inside.
        
        p = ovr_Ovrvision->GetCamImageBGRA(OVR::OV_CAMEYE_LEFT);
        p2 = ovr_Ovrvision->GetCamImageBGRA(OVR::OV_CAMEYE_RIGHT);
        
        //        unsigned char* p = ovr_Ovrvision->GetCamImageBGRA(OVR::OV_CAMEYE_LEFT);
        //        unsigned char* p2 = ovr_Ovrvision->GetCamImageBGRA(OVR::OV_CAMEYE_RIGHT);
        
        
        /*get eyes view individually*/
        
        fbo.begin();
        ovr_screen_texture.loadData(p, ovr_camWidth, ovr_camHeight, GL_BGRA);
        
        ovr_screen_texture.draw(0,0);        //<- this is causing memory increase
        
//        fbo.attachTexture(ovr_screen_texture, GL_BGRA, 0);
        
        ovr_screen_texture.loadData(p2, ovr_camWidth, ovr_camHeight, GL_BGRA);
        
        ovr_screen_texture.draw(ovr_camWidth,0); //<- this is causing memory increase

        
        fbo.end();
        
    }

}

void ofxOvrvisionPro::draw(int _x =0, int _y =0){
    if (ovr_Ovrvision->isOpen())
    {
        fbo.draw(_x, _y);
        
        
    }

}

void ofxOvrvisionPro::exit(){
    cout<<"closing..."<<endl;
    fbo.clear();
    ovr_Ovrvision->Close();
    ofSleepMillis(1000);

    //Delete object
    delete ovr_Ovrvision;

    cout<<"done"<<endl;

}

