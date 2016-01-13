#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ovrPro.init(false); //the argument decide to use PBO or not
}

//--------------------------------------------------------------
void ofApp::update(){
    ovrPro.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ovrPro.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
//        case 'p':
//            if (g_processMode == OVR::Camqt::OV_CAMQT_DMS)
//                g_processMode = OVR::Camqt::OV_CAMQT_DMSRMP;
//            else
//                g_processMode = OVR::Camqt::OV_CAMQT_DMS;
//            break;

        case 'e':
            exit();
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
    ovrPro.exit();
    std::exit(1);
}
