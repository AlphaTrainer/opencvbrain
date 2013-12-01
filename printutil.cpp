/*
 * printutil.cpp
 */


#include "printutil.h"

// Note: so fare we explicit name spacing so "using" not used
//using namespace cv;

void printArray(cv::Mat a)
{
	std::cout << "Printing array of " << a.rows << " rows and " << a.cols << " cols";

	for (int i = 0; i < a.rows; i++) {
		std::cout << std::endl;
		for (int j = 0; j < a.cols; j++) {
			std::cout << a.at<float>(i, j) << " ";
		}
	}

	std::cout << std::endl;
}
