#pragma once

#include "ofMain.h"
#include "ofxEasyAR.hpp"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"

static std::string key = "677261b33cec2755aeb14f4fe48664705Rfl9b2K8ySCqm0pOuym6QzrD8PtSBu87cXvEL0U0Hp5i1MjjQT27omy7CZGocbxi7cacb2j09OVyImCBChzCuzgpAsuhUxdxHy5ZgMAkEm0Pm0Wglzovmoj1fwdIHULU9jfxztYkB9DnQy0NVkqmk648LYXtp8V8tkh6ELB";


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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

		
		ofxEasyAR mEasyAR;

		ofImage mVideoFrame;
		double mLastFrameTimeStamp;

		ofBoxPrimitive mBox;
		ofxAssimpModelLoader mModel;
		ofLight	mLight;

};
