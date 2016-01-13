//
//  OvrPro.cpp
//  ofxOvrvision
//
//  Created by kjwu on 1/7/16.
//
//

#include "OvrPro.h"

OvrPro::OvrPro(){
    cameraMode = OVR::OV_CAMVR_FULL; //kj:1280x960 @45fps x2 ?
    
    //Create Ovrvision object
    //    ovr_Ovrvision.reset(new OVR::OvrvisionPro); // when use smart pointer
    //    ovr_Ovrvision = new OVR::OvrvisionPro; // when use regular pointer
    ofSleepMillis(1000);
    
}

OvrPro::~OvrPro(){
    if(ovr_Ovrvision.isOpen()){
        cout<<"it's open, close it "<<endl;
        ovr_Ovrvision.Close();
    }
}

void OvrPro::init(bool _usePbo = true){
    //    int locationID = 0;
    ofSetVerticalSync(true);
    usePbo = _usePbo; // if below GL4.5, uses simulator (CPU), but no memory leak, also to use this need to modify the ofBufferObject Lib a bit
    
    //    if(ovr_Ovrvision.isOpen()){
    //        cout<<"it's open, close it"<<endl;
    //        ovr_Ovrvision.Close();
    //        ofSleepMillis(1000);
    //
    //    }
    
    //    ovr_Ovrvision.Open(locationID, cameraMode); //960x950 @60fps by default
    try{
        if (ovr_Ovrvision.Open(0, OVR::OV_CAMVR_FULL, 0, NULL)){
            cout<< "Open Ovr Pro successful."<<endl;
        }
    }catch (int e){
        cout << e <<endl;
    }
    
    
    ofSleepMillis(100); //wait for 1/10 sec kj:be conservative.
    if (ovr_Ovrvision.isOpen() == false) {
        printf("Ovrvision Pro Open Error!\nPlease check whether OvrPro is connected.");
    }
    //ovr_Ovrvision.SetCameraExposure(12960);
    ovr_Ovrvision.SetCameraSyncMode(false); //kj: white balance?
    
    //OculusRightGap
    ovr_hmdGap.x = ovr_Ovrvision.GetHMDRightGap(0) * -0.01f;
    ovr_hmdGap.y = ovr_Ovrvision.GetHMDRightGap(1) * 0.01f;
    ovr_hmdGap.z = ovr_Ovrvision.GetHMDRightGap(2) * 0.01f;
    
    ovr_camWidth = ovr_Ovrvision.GetCamWidth();
    ovr_camHeight = ovr_Ovrvision.GetCamHeight();
    ofSleepMillis(1000);
    cout<<"Ovrvision Camera size: "<<ovr_camWidth<< "x"<<ovr_camHeight<<endl;
    cout<<"buffer size of the Ovrvision image:"<<ovr_Ovrvision.GetCamBuffersize()<<endl;
    
    
    if (usePbo) {
        //    https://forum.openframeworks.cc/t/ofbufferobject-and-async-camera-video-texture-upload/21824/2
        texL.allocate(ovr_camWidth,ovr_camHeight,GL_RGBA);
        pboL.allocate(ovr_camWidth*ovr_camHeight*4,  GL_STREAM_DRAW);
        auto dstBuffer = pboL.map<unsigned char>(GL_WRITE_ONLY);
        channelL.send(dstBuffer);
    }else{
        pixL= (unsigned char*)malloc(ovr_camWidth*ovr_camHeight*4);
        texL.allocate(ovr_camWidth, ovr_camHeight,GL_RGBA);
        fboL.allocate(ovr_camWidth, ovr_camHeight, GL_RGBA);
        
        
        fboL.begin();
        ofClear(255,255,255, 0);
        fboL.end();
    }
    
}

void OvrPro::update(){
    
    if (ovr_Ovrvision.isOpen())
    {
        //Full Draw
        ovr_Ovrvision.PreStoreCamData(ovr_processMode);
        //This function gets data from OvrPro inside.
        
        unsigned char* p = ovr_Ovrvision.GetCamImageBGRA(OVR::OV_CAMEYE_LEFT);
        unsigned char* p2 = ovr_Ovrvision.GetCamImageBGRA(OVR::OV_CAMEYE_RIGHT);
        
        
        if (usePbo) {
            unsigned char * dstPixels;
            channelL.receive(dstPixels);
            memcpy(dstPixels, p, ovr_camWidth*ovr_camHeight*4);
            channelLReady.send(true);
            
            bool ready ;
            if(channelLReady.tryReceive(ready)){
                pboL.unmap();
                texL.loadData(pboL,GL_BGRA,GL_UNSIGNED_BYTE);
                auto dstBuffer = pboL.map<unsigned char>(GL_WRITE_ONLY);
                channelL.send(dstBuffer);
            }
            
        }else{
            //            memcpy(pixL, p, ovr_camWidth*ovr_camHeight*4);
            
            /*get eyes view individually*/
            //            fboL.begin();
            //            texL.loadData(pixL, ovr_camWidth, ovr_camHeight, GL_BGRA); //<- this is causing memory increase?
            texL.loadData(p, ovr_camWidth, ovr_camHeight, GL_BGRA); //<- this is causing memory increase?
            fboL.attachTexture(texL, GL_BGRA, 0); // USE ATTACH,
            //            ovr_screen_textureL.draw(0,0);
            //            fboL.end();
        }
    }
    
}

void OvrPro::draw(int _x =0, int _y =0){
    if (ovr_Ovrvision.isOpen())
    {
        
        if (usePbo) {
            texL.draw(_x,_y);
        }else{
            //              fboL.draw(_x, _y);
            ofEnableNormalizedTexCoords();

//            texL.draw(0,0);
//            texL.bind();
//            ofDrawRectangle(0, 0, 1, 1);
//            texL.unbind();
            ofDisableNormalizedTexCoords();
        }
        
    }
    
}

void OvrPro::exit(){
    cout<<"closing..."<<endl;
    fboL.clear();
    ovr_Ovrvision.Close();
    ofSleepMillis(2000);
    
    //    delete ovr_Ovrvision; //if use regular pointer
    
    cout<<"done"<<endl;
    
}

