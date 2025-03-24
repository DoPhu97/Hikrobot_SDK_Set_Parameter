#include "CapThread.h"
#include <chrono>

void CapThread::threadedFunction() {
	MV_FRAME_OUT ImageInfo = { 0 };
	RawData rawData;
	int frameCount = 0;
	auto startTime = std::chrono::high_resolution_clock::now();

	while (isThreadRunning()) {
		if (Camera.GetFrameBuffer(&ImageInfo, 1000)) {
			auto currentTime = std::chrono::high_resolution_clock::now();

			// Create OpenCV Mat from camera buffer
			rawData.Img = cv::Mat(480, 640, CV_8UC1, ImageInfo.pBufAddr);

			if (!rawData.Img.empty()) {
				// Store timestamp in microseconds (unsigned int gives ~71 minutes)
				rawData.Time = static_cast<unsigned int>(
					std::chrono::duration_cast<std::chrono::microseconds>(
						currentTime.time_since_epoch()).count());
				_rawDataChannel.send(rawData);
				frameCount++;
			}

			// Free the frame buffer
			Camera.FreeFrameBuffer(&ImageInfo);

			// Calculate FPS after buffer is freed
			auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(
				currentTime - startTime).count();
			if (elapsedTime >= 1) {
				double fps = static_cast<double>(frameCount) / elapsedTime;
				printf("Cap: %.2f FPS\n", fps);
				// Reset counters
				frameCount = 0;
				startTime = currentTime;
			}
		}
	}
}