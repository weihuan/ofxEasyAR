#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//ofLog() << "begin setup" << std::endl;

	//ofSetFrameRate(30);

	mModel.loadModel("dwarf.x", true);
	mModel.setScale(0.02f, 0.02f, 0.02f);
	mModel.setRotation(0, 90, 1.0f, 0.0f, 0.0f);
	mModel.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	mModel.playAllAnimations();

	mEasyAR.setup(key);
	mEasyAR.initCamera();
	mEasyAR.loadFromJsonFile("data/targets.json", "argame");
	mEasyAR.loadFromJsonFile("data/targets.json", "idback");
	mEasyAR.loadAllFromJsonFile("data/targets2.json");
	mEasyAR.loadFromImage("data/namecard.jpg");
	mEasyAR.start();

	ofSleepMillis(1000);

	mLastFrameTimeStamp = 0.0;

}

//--------------------------------------------------------------
void ofApp::update(){

	mModel.update();

	EasyAR::Frame _frame = mEasyAR.augmenter_.newFrame(mEasyAR.tracker_);
	EasyAR::Image _image = _frame.images()[0];

	if (mLastFrameTimeStamp != _frame.timeStamp())
	{
		ofPixels _p;
		_p.setFromExternalPixels((unsigned char*)_image.data(), _image.width(), _image.height(), OF_PIXELS_BGR);
		_p.swapRgb();
		mVideoFrame.setFromPixels(_p);
		mLastFrameTimeStamp = _frame.timeStamp();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	/*mEasyAR.augmenter_.drawVideoBackground();*/

	mVideoFrame.draw(0, 0);
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate(), 2), 10, 15);

	EasyAR::Frame _frame = mEasyAR.augmenter_.newFrame(mEasyAR.tracker_);

	EasyAR::AugmentedTarget::Status status = _frame.targets()[0].status();

	if (status == EasyAR::AugmentedTarget::kTargetStatusTracked) 
	{
		EasyAR::Matrix44F projectionMatrix = EasyAR::getProjectionGL(mEasyAR.camera_.cameraCalibration(), 0.2f, 500.f);
		EasyAR::Matrix44F cameraview = EasyAR::getPoseGL(_frame.targets()[0].pose());
		EasyAR::ImageTarget target = _frame.targets()[0].target().cast_dynamic<EasyAR::ImageTarget>();
		
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);

		ofEnableDepthTest();
#ifndef TARGET_PROGRAMMABLE_GL    
		glShadeModel(GL_SMOOTH); //some model / light stuff
#endif
		mLight.enable();
		ofEnableSeparateSpecularLight();

		ofPushMatrix();

		glViewport(0, 0, 640, 480);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(&projectionMatrix.data[0]);

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(&cameraview.data[0]);

		//mBox.setScale(0.02f);
		//mBox.draw();

		mModel.drawFaces();
		ofPopMatrix();

		ofDisableDepthTest();
		mLight.disable();
		ofDisableLighting();
		ofDisableSeparateSpecularLight();

		//ofLog() << "marker detected" << std::endl;
	}


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
