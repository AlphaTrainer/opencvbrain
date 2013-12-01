/*
 * printutil.h
 *
 * take care don't overlap with brainprocessing.h
 */

#ifndef PRINTUTIL_H_
#define PRINTUTIL_H_

#include <iostream>

// NB! OpenCV 2:
#include "opencv2/core/core.hpp"

// Note: so fare we explicit name spacing so "using" not used
//using namespace cv;
//using namespace std;

void printArray(cv::Mat a );

#endif /* PRINTUTIL_H_ */
