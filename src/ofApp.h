#pragma once

#include "ofMain.h"
#include <ovrvision_pro.h>
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        int g_camWidth;
        int g_camHeight;

        //ovrvision pro related:
        ofTexture g_screen_texture;
        ofVec3f g_hmdGap;
    
        OVR::OvrvisionPro* g_pOvrvision;
        OVR::Camqt g_processMode = OVR::Camqt::OV_CAMQT_DMS;

    
        //renderer
        ofFbo fbo;
		
};
