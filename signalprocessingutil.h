/*
 * signalprocessingutil.h
 *
 * take care don't overlap with brainprocessing.h
 */

#ifndef SIGNALPROCESSINGUTIL_H_
#define SIGNALPROCESSINGUTIL_H_

#include <math.h>
#include <iostream>

// NB! OpenCV 2:
#include "opencv2/core/core.hpp"

// Note: so fare we explicit name spacing so "using" not used
//using namespace cv;

float getAreaUnderCurve(cv::Mat a, int startSample, int endSample, int Fs);

// NIECETOHAVE: should both have reference operator "&" ?
// - http://stackoverflow.com/questions/11235187/opencv-changing-mat-inside-a-function-mat-scope
void getFft(cv::Mat input, cv::Mat& dest);

#endif /* SIGNALPROCESSINGUTIL_H_ */
