#pragma once
#include "Camera.h"
#include "ofThread.h"
#include "ofThreadChannel.h"
#include "DataType.h"

class CapThread : public ofThread {

protected:
	void threadedFunction();

public:
	CapThread() {};
	~CapThread() { 
		_rawDataChannel.close();
		waitForThread();
	};
	Camera Camera;
	ofThreadChannel<RawData> &getRawDataChannel() {
		return _rawDataChannel;
	}

private:
	ofThreadChannel<RawData> _rawDataChannel;
	
};
