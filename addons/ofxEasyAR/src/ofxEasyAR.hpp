//
//  ofxEasyAR.h
//  Created by Wei Huan on 7/4/16.
//

#pragma once

#include "ofMain.h"

#include "easyar/camera.hpp"
#include "easyar/tracker.hpp"
#include "easyar/augmenter.hpp"
#include "easyar/target.hpp"
#include "easyar/frame.hpp"
#include "easyar/utility.hpp"

#include <string>

class ofxEasyAR
{
public:
	ofxEasyAR();
	~ofxEasyAR();

	void setup(std::string key);

	bool initCamera();
	void loadFromImage(const std::string& path);
	void loadFromJsonFile(const std::string& path, const std::string& targetname);
	void loadAllFromJsonFile(const std::string& path);
	bool start();
	bool stop();
	bool clear();

	//void initGL();
	//void resizeGL(int width, int height);
	//void render();
	void setPortrait(bool portrait);

//protected:
	EasyAR::CameraDevice camera_;
	EasyAR::ImageTracker tracker_;
	EasyAR::Augmenter augmenter_;
	bool portrait_;

};