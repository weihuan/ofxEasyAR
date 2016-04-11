

#include "ofxEasyAR.hpp"
#include <algorithm>



class HelloCallBack : public EasyAR::TargetLoadCallBack
{
public:
	virtual ~HelloCallBack() {};
	virtual void operator() (const EasyAR::Target target, const bool status)
	{
		//LOGI("load target: %s (%d) %s\n", target.name(), target.id(), status ? "success" : "fail");
		ofLog() << "load target: " << target.name() << " " << target.id() << " " << (status ? "success" : "fail") << std::endl;
		delete this;
	}
};

ofxEasyAR::ofxEasyAR()
{
	portrait_ = false;
}

ofxEasyAR::~ofxEasyAR()
{
	clear();
}

void ofxEasyAR::setup(std::string key)
{
	EasyAR::initialize(key.c_str());
}

bool ofxEasyAR::initCamera()
{
	bool status = true;
	status &= camera_.open(2);
	camera_.setSize(EasyAR::Vec2I(640, 480));
	status &= tracker_.attachCamera(camera_);
	return status;
}

void ofxEasyAR::loadFromImage(const std::string& path)
{
	EasyAR::ImageTarget target;
	std::string jstr = "{\n"
		"  \"images\" :\n"
		"  [\n"
		"    {\n"
		"      \"image\" : \"" + path + "\",\n"
		"      \"name\" : \"" + path.substr(0, path.find_first_of(".")) + "\"\n"
		"    }\n"
		"  ]\n"
		"}";
	target.load(jstr.c_str(), EasyAR::kStorageAssets | EasyAR::kStorageJson);
	tracker_.loadTarget(target, new HelloCallBack());
}

void ofxEasyAR::loadFromJsonFile(const std::string& path, const std::string& targetname)
{
	EasyAR::ImageTarget target;
	target.load(path.c_str(), EasyAR::kStorageAssets, targetname.c_str());
	tracker_.loadTarget(target, new HelloCallBack());
}

void ofxEasyAR::loadAllFromJsonFile(const std::string& path)
{
	EasyAR::TargetList targets;
	targets.load(path.c_str(), EasyAR::kStorageAssets);
	for (int i = 0; i < targets.size(); ++i) {
		tracker_.loadTarget(targets[i], new HelloCallBack());
	}
}

bool ofxEasyAR::start()
{
	bool status = true;
	status &= camera_.start();
	camera_.setFocusMode(EasyAR::CameraDevice::kFocusModeContinousauto);
	status &= tracker_.start();
	return status;
}

bool ofxEasyAR::stop()
{
	bool status = true;
	status &= tracker_.stop();
	status &= camera_.stop();
	return status;
}

bool ofxEasyAR::clear()
{
	bool status = true;
	status &= stop();
	status &= camera_.close();
	camera_.clear();
	tracker_.clear();
	augmenter_.clear();
	return status;
}

//void ofxEasyAR::resizeGL(int width, int height)
//{
//	EasyAR::Vec2I size = EasyAR::Vec2I(1, 1);
//	if (camera_.isOpened())
//		size = camera_.size();
//	if (size[0] == 0 || size[1] == 0)
//		return;
//	if (portrait_)
//		std::swap(size[0], size[1]);
//	float scaleRatio = std::max((float)width / (float)size[0], (float)height / (float)size[1]);
//	EasyAR::Vec2I viewport_size = EasyAR::Vec2I((int)(size[0] * scaleRatio), (int)(size[1] * scaleRatio));
//	augmenter_.setViewPort(EasyAR::Vec4I(0, height - viewport_size[1], viewport_size[0], viewport_size[1]));
//}
//
//void ofxEasyAR::initGL()
//{
//
//}
//
//void ofxEasyAR::render()
//{
//
//}
//
void ofxEasyAR::setPortrait(bool portrait)
{
	portrait_ = portrait;
}
