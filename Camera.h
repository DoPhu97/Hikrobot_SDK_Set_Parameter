#pragma once
#include "MvCameraControl.h"
#include "ofImage.h"
#include "opencv2/core.hpp"
#include <thread>
#include <atomic>

struct Data {
	cv::Mat Image;
	unsigned int FrameNum;
};

class Camera {

public:
	Camera();
	~Camera();

	bool Setup();
	bool Start();
	bool Stop();
	void Close();
	bool GetFrameBuffer(MV_FRAME_OUT* ImageInfo, unsigned int ms);
	void FreeFrameBuffer(MV_FRAME_OUT* ImageInfo);
	void GetFloatValue(const char* str, MVCC_FLOATVALUE* value);
	void SetFloatValue(const char* str, float value);
	void SetBoolValue(const char* str, bool value);
	void SetEnumValue(const char* str, unsigned int value);
	Data Data;

private:
	
	void* _Handle;
	MV_CC_DEVICE_INFO_LIST  _DeviceList;
	int _state;


};

