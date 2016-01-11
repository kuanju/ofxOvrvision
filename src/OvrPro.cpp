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
    ovr_Ovrvision.reset(new OVR::OvrvisionPro);
    ofSleepMillis(1000);

}

OvrPro::~OvrPro(){
    if(ovr_Ovrvision->isOpen()){
        cout<<"it's open, close it "<<endl;
        ovr_Ovrvision->Close();
    }
}

void OvrPro::init(bool _usePbo = true){
//    int locationID = 0;
    ofSetVerticalSync(true);
    usePbo = _usePbo;
    
    if(ovr_Ovrvision->isOpen()){
        cout<<"it's open, close it"<<endl;
        ovr_Ovrvision->Close();
        ofSleepMillis(1000);

    }
    
//    ovr_Ovrvision->Open(locationID, cameraMode); //960x950 @60fps by default
    try{
        ovr_Ovrvision->Open(0, OVR::OV_CAMVR_FULL); //960x950 @60fps by default
    }catch (int e){
        cout << e <<endl;
    }
    

    ofSleepMillis(100); //wait for 1/10 sec kj:be conservative.
    if (ovr_Ovrvision->isOpen() == false) {
        printf("Ovrvision Pro Open Error!\nPlease check whether OvrPro is connected.");
    }
    //ovr_Ovrvision->SetCameraExposure(12960);
    ovr_Ovrvision->SetCameraSyncMode(false); //kj: white balance?
    
    //OculusRightGap
    ovr_hmdGap.x = ovr_Ovrvision->GetHMDRightGap(0) * -0.01f;
    ovr_hmdGap.y = ovr_Ovrvision->GetHMDRightGap(1) * 0.01f;
    ovr_hmdGap.z = ovr_Ovrvision->GetHMDRightGap(2) * 0.01f;
    
    ovr_camWidth = ovr_Ovrvision->GetCamWidth();
    ovr_camHeight = ovr_Ovrvision->GetCamHeight();
    ofSleepMillis(1000);
    cout<<"Ovrvision Camera size: "<<ovr_camWidth<< "x"<<ovr_camHeight<<endl;
    cout<<"buffer size of the Ovrvision image:"<<ovr_Ovrvision->GetCamBuffersize()<<endl;
    

    if (usePbo) {
        //    https://forum.openframeworks.cc/t/ofbufferobject-and-async-camera-video-texture-upload/21824/2
        tex.allocate(ovr_camWidth,ovr_camHeight,GL_RGBA);
        pbo.allocate(ovr_camWidth*ovr_camHeight*4,  GL_STREAM_DRAW);
        auto dstBuffer = pbo.map<unsigned char>(GL_WRITE_ONLY);
        channel.send(dstBuffer);
    }else{
        ovr_screen_texture.allocate(ovr_camWidth, ovr_camHeight,GL_RGBA);
        fbo.allocate(ovr_camWidth*2, ovr_camHeight, GL_RGBA);
        
        fbo.begin();
        ofClear(255,255,255, 0);
        fbo.end();
    }

}

void OvrPro::update(){
    
    if (ovr_Ovrvision->isOpen())
    {
        //Full Draw
        ovr_Ovrvision->PreStoreCamData(ovr_processMode);
        //This function gets data from OvrPro inside.
        
        unsigned char* p = ovr_Ovrvision->GetCamImageBGRA(OVR::OV_CAMEYE_LEFT);
        unsigned char* p2 = ovr_Ovrvision->GetCamImageBGRA(OVR::OV_CAMEYE_RIGHT);
        

        if (usePbo) {
            unsigned char * dstPixels;
            channel.receive(dstPixels);
            memcpy(dstPixels, p, ovr_camWidth*ovr_camHeight*4);
            channelReady.send(true);

        }else{

        
            /*get eyes view individually*/
            
            fbo.begin();
            ovr_screen_texture.loadData(p, ovr_camWidth, ovr_camHeight, GL_BGRA); //<- this is causing memory increase
            ovr_screen_texture.draw(0,0);

    //        fbo.attachTexture(ovr_screen_texture, GL_BGRA, 0);
            
            ovr_screen_texture.loadData(p2, ovr_camWidth, ovr_camHeight, GL_BGRA); //<- this is causing memory increase
            ovr_screen_texture.draw(ovr_camWidth,0); //<- this is causing memory increase

            
            fbo.end();
        }
    }

}

void OvrPro::draw(int _x =0, int _y =0){
    if (ovr_Ovrvision->isOpen())
    {
        
        if (usePbo) {
            bool ready ;
            if(channelReady.tryReceive(ready)){
                pbo.unmap();
                tex.loadData(pbo,GL_BGRA,GL_UNSIGNED_BYTE);
                auto dstBuffer = pbo.map<unsigned char>(GL_WRITE_ONLY);
                channel.send(dstBuffer);
                tex.draw(_x,_y);
            }
        }else{
                fbo.draw(_x, _y);
//              ovr_screen_texture.draw(0,0);
        }

    }

}

void OvrPro::exit(){
    cout<<"closing..."<<endl;
    fbo.clear();
    ovr_Ovrvision->Close();
    ofSleepMillis(2000);
    
//    delete ovr_Ovrvision; //if use regular pointer
    
    cout<<"done"<<endl;

}

