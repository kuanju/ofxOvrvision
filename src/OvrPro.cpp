//
//  OvrPro.cpp
//  ofxOvrvision
//
//  Created by kjwu on 1/7/16.
//
//

#include "OvrPro.h"

OvrPro::OvrPro(){
    cameraMode = OVR::OV_CAMVR_FULL; //960x950 @60fps
    
    //Create Ovrvision object
    //    ovr_Ovrvision.reset(new OVR::OvrvisionPro); // when use smart pointer
    //    ovr_Ovrvision = new OVR::OvrvisionPro; // when use regular pointer
    ofSleepMillis(1000);
    
}

OvrPro::~OvrPro(){
//    if(ovr_Ovrvision.isOpen()){
//        cout<<"[OvrPro] "<<"it's open, close it "<<endl;
//        ovr_Ovrvision.Close();
//    }
}

void OvrPro::init(){
    ofSetVerticalSync(true);
    
    try{
        if (ovr_Ovrvision.Open(0, OVR::OV_CAMVR_FULL, 0, NULL)){
            cout<<"[OvrPro] "<< "Open Ovr Pro successful."<<endl;
        }
    }catch (int e){
        cout << e <<endl;
    }
    
    
    ofSleepMillis(100); //wait for 1/10 sec kj:be conservative.
    if (ovr_Ovrvision.isOpen() == false) {
        printf("[OvrPro] Ovrvision Pro Open Error!\nPlease check whether OvrPro is connected.");
    }
    
    //    ovr_Ovrvision.SetCameraExposure(30000); //12960
    ovr_Ovrvision.SetCameraSyncMode(false); //kj: white balance?
    
    ovr_camWidth = ovr_Ovrvision.GetCamWidth();
    ovr_camHeight = ovr_Ovrvision.GetCamHeight();
    
    cout<<"[OvrPro] "<<"Ovrvision Camera size: "<<ovr_camWidth<< "x"<<ovr_camHeight<<endl;
    cout<<"[OvrPro] "<<"buffer size of the Ovrvision image:"<<ovr_Ovrvision.GetCamBuffersize()<<endl;
    
    
    //Allocate frame storages
    pixL= (unsigned char*)malloc(ovr_camWidth*ovr_camHeight*4);
//    texL.allocate(ovr_camWidth, ovr_camHeight,GL_RGBA);
    
//    pixR= (unsigned char*)malloc(ovr_camWidth*ovr_camHeight*4);
//    texR.allocate(ovr_camWidth, ovr_camHeight,GL_RGBA);
    
    /********* Future Todo: **********/
    
    //    OculusRightGap
    //    ovr_hmdGap.x = ovr_Ovrvision.GetHMDRightGap(0) * -0.01f;
    //    ovr_hmdGap.y = ovr_Ovrvision.GetHMDRightGap(1) * 0.01f;
    //    ovr_hmdGap.z = ovr_Ovrvision.GetHMDRightGap(2) * 0.01f;
    
    
    //    if (usePbo) {
    //        //https://forum.openframeworks.cc/t/ofbufferobject-and-async-camera-video-texture-upload/21824/2
    //        texL.allocate(ovr_camWidth,ovr_camHeight,GL_RGBA);
    //        pboL.allocate(ovr_camWidth*ovr_camHeight*4,  GL_STREAM_DRAW);
    //        auto dstBufferL = pboL.map<unsigned char>(GL_WRITE_ONLY);
    //        channelR.send(dstBufferL);
    //        texR.allocate(ovr_camWidth,ovr_camHeight,GL_RGBA);
    //        pboR.allocate(ovr_camWidth*ovr_camHeight*4,  GL_STREAM_DRAW);
    //        auto dstBufferR = pboR.map<unsigned char>(GL_WRITE_ONLY);
    //        channelR.send(dstBufferR);
    //    }
    
}

void OvrPro::update(){
    
    if (ovr_Ovrvision.isOpen())
    {
        //Full Draw
        ovr_Ovrvision.PreStoreCamData(ovr_processMode);
        //This function gets data from OvrPro inside.
        
        pixL = ovr_Ovrvision.GetCamImageBGRA(OVR::OV_CAMEYE_LEFT);
//        pixR = ovr_Ovrvision.GetCamImageBGRA(OVR::OV_CAMEYE_RIGHT);
        
//        texL.loadData(pixL, ovr_camWidth, ovr_camHeight, GL_BGRA); //<- this is causing memory increase?
//        texR.loadData(pixR, ovr_camWidth, ovr_camHeight, GL_BGRA); //<- this is causing memory increase?
        
        /********* Future Todo: **********/
        
        //    if (usePbo) {
        //        unsigned char * dstPixelsL;
        //        channelL.receive(dstPixelsL);
        //        memcpy(dstPixelsL, p, ovr_camWidth*ovr_camHeight*4);
        //        channelLReady.send(true);
        //
        //        bool readyL ;
        //        if(channelLReady.tryReceive(readyL)){
        //            pboL.unmap();
        //            texL.loadData(pboL,GL_BGRA,GL_UNSIGNED_BYTE);
        //            auto dstBufferL = pboL.map<unsigned char>(GL_WRITE_ONLY);
        //            channelL.send(dstBufferL);
        //        }
        //
        //
        //        unsigned char * dstPixelsR;
        //        channelR.receive(dstPixelsR);
        //        memcpy(dstPixelsR, p2, ovr_camWidth*ovr_camHeight*4);
        //        channelRReady.send(true);
        //
        //        bool readyR ;
        //        if(channelRReady.tryReceive(readyR)){
        //            pboR.unmap();
        //            texR.loadData(pboR,GL_BGRA,GL_UNSIGNED_BYTE);
        //            auto dstBufferR = pboR.map<unsigned char>(GL_WRITE_ONLY);
        //            channelR.send(dstBufferR);
        //        }
        //    }
        
        
    }
    
}

void OvrPro::draw(int _x =0, int _y =0){
    if (ovr_Ovrvision.isOpen())
    {
        
        texL.draw(_x,_y);
        texR.draw(_x+ovr_camWidth,_y);
        
        /********* Future Todo: **********/
        //if (usePbo) {
        //    texL.draw(_x,_y);
        //    texR.draw(_x+ovr_camWidth,_y);
        //
        //}
        
    }
    
}

ofTexture OvrPro::getTextureLeft(){
    return texL;
}

ofTexture OvrPro::getTextureRight(){
    return texR;
}

void OvrPro::exit(){
    cout<<"[OvrPro] "<<"closing..."<<endl;
    ovr_Ovrvision.Close();
    ofSleepMillis(2000);
    //delete ovr_Ovrvision; //if use regular pointer
    cout<<"[OvrPro] "<<"done"<<endl;
    
}
