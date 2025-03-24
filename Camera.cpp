#include "Camera.h"

Camera::Camera() {
	_Handle = nullptr;
	memset(&_DeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
	int _state = -1;
}

Camera::~Camera() {
	Close();
}

bool Camera::Setup() {
	
	MV_CC_Initialize();//SDK Initialization

	_state = MV_CC_EnumDevices(MV_USB_DEVICE, &_DeviceList);//enum USB device
	if(_state != MV_OK) return false;
	if (_DeviceList.nDeviceNum <= 0) 	return false;

	_state = MV_CC_CreateHandle(&_Handle, _DeviceList.pDeviceInfo[0]);
	if (_state != MV_OK) {
		_Handle = NULL;
		return false;
	}

	_state = MV_CC_OpenDevice(_Handle);//Open device
	if (_state == !MV_OK) {
		MV_CC_DestroyHandle(_Handle);
		_Handle = NULL;
		return false;
	}

	SetEnumValue("TriggerMode", MV_TRIGGER_MODE_OFF);//Set trigger mode off

	SetEnumValue("PixelFormat", PixelType_Gvsp_Mono8);
	SetEnumValue("LineSelector", 1);
	SetEnumValue("LineMode", 8);
	SetBoolValue("StrobeEnable", true);
	SetFloatValue("AcquisitionFrameRate", 816);

	return true;

}

bool Camera::Start() {

	_state = MV_CC_StartGrabbing(_Handle);
	if (_state == MV_OK) return true;
	else return false;
}

bool Camera::Stop() {
	_state = MV_CC_StopGrabbing(_Handle);
	if (_state == MV_OK) return true;
	else return false;
}

void Camera::Close() {

	_state = MV_CC_CloseDevice(_Handle);
}

void Camera::GetFloatValue(const char* str, MVCC_FLOATVALUE* value) {

	MV_CC_GetFloatValue(_Handle, str, value);
}


void Camera::SetEnumValue(const char* str, unsigned int value) {

	_state = MV_CC_SetEnumValue(_Handle, str, value);
	if (_state == MV_OK) {
		printf("Set %s sucessfully\n", str);
	}
	else {
		printf("Set %s fail\n", str);
	}
	
}

void Camera::SetBoolValue(const char* str, bool value) {

	_state = MV_CC_SetBoolValue(_Handle, str, value);
	if (_state == MV_OK) {
		printf("Set %s sucessfully\n", str);
	}
	else {
		printf("Set %s fail\n", str);
	}
}

void Camera::SetFloatValue(const char* str, float value) {

	_state = MV_CC_SetFloatValue(_Handle, str, value);
	if (_state == MV_OK) {
		printf("Set %s sucessfully\n", str);
	}
	else {
		printf("Set %s fail\n", str);
	}
}


bool Camera::GetFrameBuffer(MV_FRAME_OUT* ImageInfo, unsigned int ms) {
	
	_state =  MV_CC_GetImageBuffer(_Handle, ImageInfo, ms);
	if (_state == MV_OK) return true;
	else return false;
}

void Camera::FreeFrameBuffer(MV_FRAME_OUT* ImageInfo) {
	
	MV_CC_FreeImageBuffer(_Handle, ImageInfo);
}

