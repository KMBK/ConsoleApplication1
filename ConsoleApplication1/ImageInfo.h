#include <opencv2/opencv.hpp>

#pragma once
class ImageInfo
{
public:
	cv::Mat Image;
	std::string Name;
	std::string Path;
};