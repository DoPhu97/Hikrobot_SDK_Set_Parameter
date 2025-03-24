#pragma once
#include <opencv2/core.hpp>

struct RawData {
	cv::Mat Img;
	unsigned int Time;  //Timestamp of the frame
};

struct GlintCandiate {
	std::pair<cv::Point2f, cv::Point2f> LEye;
	std::pair<cv::Point2f, cv::Point2f> REye;
};

struct EyeData {
	cv::Mat Img;
	cv::Point2f Pupil;
	cv::Point2f LGlint;
	cv::Point2f RGlint;
};

struct ProData {
	EyeData LEye;
	EyeData REye;
	unsigned int Time;
};

