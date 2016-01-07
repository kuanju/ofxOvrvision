#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int locationID = 0;
    OVR::Camprop cameraMode = OVR::OV_CAMVR_FULL; //1280x960 @45fps x2
    ofSetVerticalSync(true);
    
    
    //Create Ovrvision object
    g_pOvrvision = new OVR::OvrvisionPro();
    if (g_pOvrvision->Open(locationID, cameraMode) == 0) {	//Open 960x950@60 default
        printf("Ovrvision Pro Open Error!\nPlease check whether OvrvisionPro is connected.");
    }
    
    g_pOvrvision->SetCameraSyncMode(false);

    //OculusRightGap
    g_hmdGap.x = g_pOvrvision->GetHMDRightGap(0) * -0.01f;
    g_hmdGap.y = g_pOvrvision->GetHMDRightGap(1) * 0.01f;
    g_hmdGap.z = g_pOvrvision->GetHMDRightGap(2) * 0.01f;
    
    g_camWidth = g_pOvrvision->GetCamWidth();
    g_camHeight = g_pOvrvision->GetCamHeight();
    
    cout<<g_camWidth<< ":"<<g_camHeight<<endl;
    
    g_screen_texture.allocate(g_camWidth,g_camHeight,GL_RGBA);
    fbo.allocate(g_camWidth*2, g_camHeight, GL_RGBA);

    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (g_pOvrvision->isOpen())
    {
        //Full Draw
        g_pOvrvision->PreStoreCamData(g_processMode);
//        unsigned char* p = g_pOvrvision->GetCamImageBGRA(OVR::OV_CAMEYE_LEFT);
//        unsigned char* p2 = g_pOvrvision->GetCamImageBGRA(OVR::OV_CAMEYE_RIGHT);
        
        g_screen_texture.loadData(g_pOvrvision->GetCamImageBGRA(OVR::OV_CAMEYE_LEFT), g_camWidth, g_camHeight, GL_BGRA);
        
        fbo.begin();
        g_screen_texture.draw(0,0);
        fbo.end();

        g_screen_texture.loadData(g_pOvrvision->GetCamImageBGRA(OVR::OV_CAMEYE_RIGHT), g_camWidth, g_camHeight, GL_BGRA);

        fbo.begin();
        g_screen_texture.draw(g_camWidth,0);
        fbo.end();

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (g_pOvrvision->isOpen())
    {
        fbo.draw(0, 0);

    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'p':
            if (g_processMode == OVR::Camqt::OV_CAMQT_DMS)
                g_processMode = OVR::Camqt::OV_CAMQT_DMSRMP;
            else
                g_processMode = OVR::Camqt::OV_CAMQT_DMS;
            break;
            
        default:
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::exit(){
    //Delete object
    delete g_pOvrvision;
    
    /*------------------------------------------------------------------*/
    return 0;

}
